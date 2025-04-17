#pragma once
 
#include <iostream>
 
namespace conf
 
{
    float width = 800;
    float height = 499;

    struct center
    {
        int x=width/2,y=height/2;
    };

    struct playerCarPosition
    {
        int x=375,y=300;
    };
    struct NPCCarPosition
    {
        int x=375,y=-450;
    };

    
    ///////////////////////////
    // car speed vs scroll speed
    // car speed will be the representative speed, it will show whether the speed of the car
    // ! DO NOT USE THESE VALUES DIRECTLY IN MAIN
    float playerCarSpeed = 400.f;
    float NPCCarSpeed = 280.f;
    
    // scroll speed is the actual acting speed used in the game
    // it will be used to scroll the road and the cars
    float roadScrollSpeed = playerCarSpeed;
    float NPCScrollSpeed = roadScrollSpeed - NPCCarSpeed;
    float playerScrollSpeed = roadScrollSpeed - playerCarSpeed; // is 0,
    ///////////////////////////

    float CarsScale = 0.6f;

    std::string road = "res/road.png";
    std::string blueCar = "res/Cars/Cars-04-37.png";
    std::string whiteCar = "res/Cars/Cars-04-15.png";
    std::string orangeCar = "res/OrangeCar.png";
    std::string windowTitle = "Racing Game by Rafay & Salman";

    // background color
    sf::Color darkGreen = sf::Color(5, 128, 15); // dark green color darkGreen

}