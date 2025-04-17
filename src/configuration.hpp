#pragma once
 
#include <iostream>
 
namespace conf
 
{
    float width = 1000;
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
        int x=348,y=-450;
    };

    
    
    

    
    ///////////////////////////
    // car speed vs scroll speed
    // car speed will be the representative speed, it will show whether the speed of the car
    // ! DO NOT USE THESE VALUES DIRECTLY IN MAIN
    float playerCarSpeed = 1.f;
    float playerCarTopSpeed = 600.f;
    float playerCarAcceleration = 20.f;
    float roadAcceleration = playerCarAcceleration;
    float NPCCarSpeed = 280.f;
    
    // scroll speed is the actual acting speed used in the game
    // it will be used to scroll the road and the cars
    float roadScrollSpeed = playerCarSpeed;
    float NPCScrollSpeed = roadScrollSpeed - NPCCarSpeed; // should this be redefined in main ?
    float playerScrollSpeed = roadScrollSpeed - playerCarSpeed; // is 0,
    ///////////////////////////

    


    float CarsScale = 0.6f;

    std::string road = "res/road.png";
    
    struct carColor {
        std::string red1      = "res/Cars/Cars-04-01.png";
        std::string black1    = "res/Cars/Cars-04-02.png";
        std::string yellow1   = "res/Cars/Cars-04-03.png";
        std::string blue1     = "res/Cars/Cars-04-04.png";
        std::string purple1   = "res/Cars/Cars-04-05.png";
        std::string green1    = "res/Cars/Cars-04-06.png";
        std::string orange1   = "res/Cars/Cars-04-07.png";
        std::string brown1    = "res/Cars/Cars-04-08.png";
        std::string red2      = "res/Cars/Cars-04-09.png";
        std::string gray1     = "res/Cars/Cars-04-10.png";
        std::string cream     = "res/Cars/Cars-04-11.png";
        std::string blue2     = "res/Cars/Cars-04-12.png";
        std::string pink1     = "res/Cars/Cars-04-13.png";
        std::string lime      = "res/Cars/Cars-04-14.png";
        std::string white     = "res/Cars/Cars-04-15.png";
        std::string peach     = "res/Cars/Cars-04-16.png";
        std::string brown2    = "res/Cars/Cars-04-17.png";
        std::string darkgray  = "res/Cars/Cars-04-18.png";
        std::string yellow2   = "res/Cars/Cars-04-19.png";
        std::string navy      = "res/Cars/Cars-04-20.png";
        std::string purple2   = "res/Cars/Cars-04-21.png";
        std::string green2    = "res/Cars/Cars-04-22.png";
        std::string orange2   = "res/Cars/Cars-04-23.png";
        std::string black2    = "res/Cars/Cars-04-24.png";
        std::string red3      = "res/Cars/Cars-04-25.png";
        std::string brown3    = "res/Cars/Cars-04-26.png";
        std::string yellow3   = "res/Cars/Cars-04-27.png";
        std::string blue3     = "res/Cars/Cars-04-28.png";
        std::string pink2     = "res/Cars/Cars-04-29.png";
        std::string green3    = "res/Cars/Cars-04-30.png";
        std::string gray2     = "res/Cars/Cars-04-31.png";
        std::string beige     = "res/Cars/Cars-04-32.png";
        std::string red4      = "res/Cars/Cars-04-33.png";
        std::string gray3     = "res/Cars/Cars-04-34.png";
        std::string yellow4   = "res/Cars/Cars-04-35.png";
        std::string blue4     = "res/Cars/Cars-04-36.png";
        std::string purple3   = "res/Cars/Cars-04-37.png";
        std::string green4    = "res/Cars/Cars-04-38.png";
        std::string orange3   = "res/Cars/Cars-04-39.png";
        std::string brown4    = "res/Cars/Cars-04-40.png";
        std::string peach2    = "res/Cars/Cars-04-41.png";
        std::string red5      = "res/Cars/Cars-04-42.png";
        std::string gray4     = "res/Cars/Cars-04-43.png";
        std::string yellow5   = "res/Cars/Cars-04-44.png";
        std::string blue5     = "res/Cars/Cars-04-45.png";
        std::string green5    = "res/Cars/Cars-04-46.png";
        std::string orange4   = "res/Cars/Cars-04-47.png";
        std::string brown5    = "res/Cars/Cars-04-48.png";
    };

    // new keyword to deal with
    extern carColor carColors; // Declare carColors as an external instance
    extern std::string* colors[48]; // Declare colors as an external array
    
    std::string windowTitle = "Racing Game by Rafay & Salman";

    // background color
    sf::Color darkGreen = sf::Color(5, 128, 15); // dark green color darkGreen

}