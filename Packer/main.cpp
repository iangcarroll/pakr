//
//  main.cpp
//  Packer
//
//  Created by Ian Carroll on 1/5/17.
//  Copyright © 2017 Ian Carroll. All rights reserved.
//

#include <cassert>
#include <cstdint>
#include <iostream>
#include <CoreServices/CoreServices.h>

#include <mach-o/arch.h>
#include <mach-o/fat.h>
#include <mach-o/dyld.h>
#include <mach/mach.h>
#include <sys/mman.h>

#include "Onion.hpp"
#include "packed.h"

typedef void (*unpacked)();

char alignedFileContents[] = {
#include "bundle.h"
};

size_t alignedFileSize;

void loadFile() {
    alignedFileSize = main_bundle_len;

    int err = vm_allocate(mach_task_self(), (vm_address_t *) &alignedFileContents, alignedFileSize + 1, true);
    assert(err == 0);
    
    memcpy(alignedFileContents, main_bundle, alignedFileSize);
}

void startFile() {
    NSObjectFileImage image;
    NSObjectFileImageReturnCode returnCode = NSCreateObjectFileImageFromMemory(alignedFileContents, alignedFileSize, &image);
    
    assert(returnCode == NSObjectFileImageSuccess);
    
    NSModule module = NSLinkModule(image, "main.bundle", NSLINKMODULE_OPTION_BINDNOW);
    NSSymbol symbol = NSLookupSymbolInModule(module, "_main");
    
    unpacked func = (unpacked) NSAddressOfSymbol(symbol);
    assert(func != NULL);
    
    func();
}

int main(int argc, const char * argv[]) {
    srand((unsigned) time(NULL));

    auto onion = Onion();
    
    std::string result = onion.pack("abc");
    std::cout << result << std::endl;
    
    result = onion.unpack(result);
    std::cout << result << std::endl;
    
    loadFile();
    startFile();
    
    // uint8_t * binary = onion.getBinaryConfiguration();

    return 0;
}
