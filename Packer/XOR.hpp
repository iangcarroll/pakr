//
//  XOR.hpp
//  Packer
//
//  Created by Ian Carroll on 1/5/17.
//  Copyright © 2017 Ian Carroll. All rights reserved.
//

#ifndef XOR_hpp
#define XOR_hpp

#include <cstdlib>
#include <iostream>
#include <string>

class XOR {
public:
    static std::string pack(std::string data, bool shouldUnpack);
    static std::string unpack(std::string data);

private:
    static char applyXor(char byte, char seed);
};

#endif /* XOR_hpp */
