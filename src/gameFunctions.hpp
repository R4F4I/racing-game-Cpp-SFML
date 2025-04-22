#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "elements.hpp"

// contains non-specific functions aka function that do not change global variables

namespace func{
    int getRandomNumber(sf::Clock& clock, int min = 0, int max = 47);

}

namespace load{

    int loadNPC(elements::PlayerCar& pc,sf::Texture& t,std::string array[] ,int carColorIndex,int x,int y,float carScale);

}