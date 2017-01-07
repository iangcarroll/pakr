//
//  Onion.cpp
//  Packer
//
//  Created by Ian Carroll on 1/5/17.
//  Copyright © 2017 Ian Carroll. All rights reserved.
//

#include "Onion.hpp"

Onion::Onion() {
    availableLayers = std::map<int, packFunc> {
        {0, &XOR::pack},
    };

    const size_t possibleLayers = availableLayers.size();
    const int numberOfLayers = rrand(ONION_MIN_LAYERS, ONION_MAX_LAYERS);
    
    std::cout << "Selected " << numberOfLayers << " layers." << std::endl;

    for (auto i = 0; i < numberOfLayers; i++) {
        auto chosenLayer = rrand(0, possibleLayers - 1);
        layers.insert(layers.end(), (int) chosenLayer);
    }
}

std::string Onion::pack(std::string data) {
    for (auto const& funcIndex : layers) {
        packFunc packer = availableLayers.at(funcIndex);
        data = packer(data, false);
    }
    
    return data;
}

std::string Onion::unpack(std::string data) {
    std::vector<int> reversed = layers;
    std::reverse(reversed.begin(), reversed.end());
    
    for (auto const& funcIndex : reversed) {
        packFunc packer = availableLayers.at(funcIndex);
        data = packer(data, true);
    }
    
    return data;
}

uint8_t * Onion::getBinaryConfiguration() {
    std::cout << "Size of layers is " << layers.size() << std::endl;

    uint8_t * binary = (uint8_t *) malloc(layers.size() + 1);
    
    binary[0] = layers.size();

    for (int i = 1; i <= layers.size(); i++) {
        binary[i] = (uint8_t) layers.at(i - 1) + 1;
    }

    return binary;
}

void Onion::importBinaryConfiguration(uint8_t * data) {
    layers.clear();
    
    auto size = data[0];
    
    for (int i = 0; i < size; i++) {
        layers.insert(layers.end(), data[i + 1]);
    }
}
