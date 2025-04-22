#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <random>
#include <iostream>
#include "elements.hpp"

namespace func{
    // rand gen
    int getRandomNumber(sf::Clock& clock, int min = 0, int max = 47) {
        static std::random_device rd; // Non-deterministic seed
        static std::mt19937 engine(rd()); // Mersenne Twister engine
        std::uniform_int_distribution<int> dist(min, max); // Uniform distribution
        return dist(engine); // Generate a random integer
    }
}

namespace load{
    // specialized function loaded only once in main
    //             car sprite,            car texture,   string to fetch texture from, car color index,        x position,       y position
int loadNPC(elements::PlayerCar& pc,sf::Texture& t,std::string refArray[] ,int carColorIndex,int x,int y,float carScale){
        if (!t.loadFromFile(refArray[carColorIndex])) {
            std::cerr << "Failed to load NPC texture\n";
            return -1;
        }
        
        pc = elements::PlayerCar(t);
        
        pc.setScale(static_cast<float>(carScale), static_cast<float>(carScale)); // Scale if needed
        pc.setPosition(x, y); // Center near bottom
    
        return 0;
    }
}
