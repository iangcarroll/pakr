//
//  XOR.cpp
//  Packer
//
//  Created by Ian Carroll on 1/5/17.
//  Copyright © 2017 Ian Carroll. All rights reserved.
//

#include "XOR.hpp"

std::string XOR::pack(std::string data, bool shouldUnpack) {
    if (shouldUnpack)
        return unpack(data);
    
    const char seed = (uint8_t) rand();

    std::string packed = std::string(&seed, 1);
    
    for (char& c : data) {
        packed += applyXor(c, seed);
    }

    return packed;
}

std::string XOR::unpack(std::string data) {
    char seed = data.at(0);
    data = data.substr(1);

    for (char& c : data) {
        c = applyXor(c, seed);
    }
    
    return data;
}

char XOR::applyXor(char byte, char seed) {
    return byte ^ seed;
}
