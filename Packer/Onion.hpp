//
//  Onion.hpp
//  Packer
//
//  Created by Ian Carroll on 1/5/17.
//  Copyright © 2017 Ian Carroll. All rights reserved.
//

#ifndef Onion_hpp
#define Onion_hpp

#define ONION_MIN_LAYERS 3200
#define ONION_MAX_LAYERS 3500

#include <cstdlib>
#include <fcntl.h>
#include <map>
#include <iostream>
#include <string>
#include <sys/mman.h>
#include <unistd.h>
#include <vector>

#include "XOR.hpp"

// This is pretty sad, but alas.
typedef std::string (*packFunc)(std::string data, bool unpack);

#define rrand(min, max) rand() % (max - min + 1) + min

class Onion {
public:
    std::vector<int> layers = std::vector<int>();
    std::map<int, packFunc> availableLayers = std::map<int, packFunc>();
    
    Onion();

    std::string pack(std::string input);
    std::string unpack(std::string data);

    uint8_t * getBinaryConfiguration();
    void importBinaryConfiguration(uint8_t * data);
};

#endif /* Onion_hpp */
