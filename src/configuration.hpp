#pragma once
 
#include <iostream>
 
namespace conf
 
{
 
    struct playerCarPosition
    {
        int x=375;
        int y=450;
    };
    
    

    float width = 800;
    float height = 600;
    float scrollSpeed = 200.f;

    float playerCarSpeed = 300.f;
    float CarsScale = 0.2f;

    std::string road = "res/road.png";
    std::string blueCar = "res/BlueCar.png";


}