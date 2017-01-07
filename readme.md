## pakr
An in-memory packer for macOS Mach-O bundles.

### How It Works
Pakr applies reversible transformations to your compiled bundle and stores the transformed bundle in your new binary (called a "stub"). The stub will reverse the transformations and execute your bundle, all without writing a file. Pakr is meant for obfuscation, not compression. Pakr will repeatedly apply transformations thousands of times, likely resulting in a larger file.

Pakr relies on the macOS API `NSCreateObjectFileImageFromMemory`. It has been deprecated since macOS 10.5, but seems unlikely to go away as the newer APIs have no replacement. After loading the object file, it calls `NSLookupSymbolInModule` to get the address of `main`, and then invokes it.

Transformations are trivial to write; simply define a `pack` and `unpack` function that take and receive strings. Pakr is best used with your own transformations to make extracting the original harder. Of course, once your bundle is loaded into memory, it can simply be extracted. It makes reverse engineering more difficult, not impossible.

#### Simplified Example
```
std::string pack(std::string data, bool shouldUnpack) {
    if (shouldUnpack)
        return unpack(data);
    
    const char seed = rand();

    std::string packed = std::string(&seed, 1);
    
    for (char& c : data) {
        packed += applyXor(c, seed);
    }

    return packed;
}

std::string unpack(std::string data) {
    char seed = data.at(0);
    data = data.substr(1);

    for (char& c : data) {
        c = applyXor(c, seed);
    }
    
    return data;
}
```

### Usage
**These steps likely do not work at this point.** 

Pakr can only load 64-bit Mach-O "bundles" (MH_BUNDLE). Compiling your code into a bundle should be possible with the clang `-bundle` flag:
```
% clang -bundle -o main.bundle main.c
% file main.bundle                   
main.bundle: Mach-O 64-bit bundle x86_64
```

Pakr will invoke the `main` function with no arguments.

After compiling your bundle, open the project in XCode and build the builder. The stub has a `bundle.h` file that the builder will overwrite.
```
./builder pack < ./path/to/your/bundle > ./path/to/bundle.h
```

Then build the stub with XCode. When executed, your stub will decode the bundle and execute the `main` function.