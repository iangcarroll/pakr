//
//  main.cpp
//  builder
//
//  Created by Ian Carroll on 1/6/17.
//  Copyright © 2017 Ian Carroll. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>

#include "Onion.hpp"

int main(int argc, const char * argv[]) {
    std::stringstream stream = std::stringstream();

    for (std::string line; std::getline(std::cin, line);) {
        stream << line << std::endl;
    }
    
    Onion onion = Onion();
    
    std::cout << stream.str() << std::endl;
}
