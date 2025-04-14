#pragma once
 
#include <iostream>
 
namespace conf
 
{
 
    struct playerCarPosition
    {
        int x=375,y=450;
    };
    
    

    float width = 800;
    float height = 499;
    float scrollSpeed = 200.f;

    float playerCarSpeed = 300.f;
    float CarsScale = 0.2f;

    std::string road = "res/road.png";
    std::string blueCar = "res/BlueCar.png";
    std::string orangeCar = "res/OrangeCar.png";
    std::string windowTitle = "Racing Game with Textures";

    // background color
    sf::Color bgColor = sf::Color(5, 128, 15); // dark green color

}