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
    struct NPC1CarPosition
    {
        int x=404,y=-450;
    };
    struct NPC2CarPosition
    {
        int x=404,y=-1700;
    };

    
    
    

    
    ///////////////////////////
    // car speed vs scroll speed
    // car speed will be the representative speed, it will show whether the speed of the car
    // ! DO NOT USE THESE VALUES DIRECTLY IN MAIN
    float playerCarSpeed = 1.f;
    float playerCarTopSpeed = 600.f;
    float playerCarAcceleration = 20.f;
    float roadAcceleration = playerCarAcceleration;
    float NPC1CarSpeed = 380.f;
    float NPC2CarSpeed = 180.f;
    
    // scroll speed is the actual acting speed used in the game
    // it will be used to scroll the road and the cars
    float roadScrollSpeed = playerCarSpeed;
    float NPC1ScrollSpeed = roadScrollSpeed - NPC1CarSpeed; // should this be redefined in main ?
    float NPC2ScrollSpeed = roadScrollSpeed - NPC2CarSpeed; // should this be redefined in main ?
    float playerScrollSpeed = roadScrollSpeed - playerCarSpeed; // is 0,
    ///////////////////////////




    float CarsScale = 0.6f;

    std::string road = "res/road.png";
    
    struct carColor {
        std::string red1 = "res/Cars/Cars-04-01.png",black1 = "res/Cars/Cars-04-02.png",yellow1 = "res/Cars/Cars-04-03.png",blue1 = "res/Cars/Cars-04-04.png",purple1 = "res/Cars/Cars-04-05.png",green1 = "res/Cars/Cars-04-06.png",orange1 = "res/Cars/Cars-04-07.png",brown1 = "res/Cars/Cars-04-08.png",red2 = "res/Cars/Cars-04-09.png",gray1 = "res/Cars/Cars-04-10.png",cream = "res/Cars/Cars-04-11.png",blue2 = "res/Cars/Cars-04-12.png",pink1 = "res/Cars/Cars-04-13.png",lime = "res/Cars/Cars-04-14.png",white = "res/Cars/Cars-04-15.png",peach = "res/Cars/Cars-04-16.png",brown2 = "res/Cars/Cars-04-17.png",darkgray = "res/Cars/Cars-04-18.png",yellow2 = "res/Cars/Cars-04-19.png",navy = "res/Cars/Cars-04-20.png",purple2 = "res/Cars/Cars-04-21.png",green2 = "res/Cars/Cars-04-22.png",orange2 = "res/Cars/Cars-04-23.png",black2 = "res/Cars/Cars-04-24.png",red3 = "res/Cars/Cars-04-25.png",brown3 = "res/Cars/Cars-04-26.png",yellow3 = "res/Cars/Cars-04-27.png",blue3 = "res/Cars/Cars-04-28.png",pink2 = "res/Cars/Cars-04-29.png",green3 = "res/Cars/Cars-04-30.png",gray2 = "res/Cars/Cars-04-31.png",beige = "res/Cars/Cars-04-32.png",red4 = "res/Cars/Cars-04-33.png",gray3 = "res/Cars/Cars-04-34.png",yellow4 = "res/Cars/Cars-04-35.png",blue4 = "res/Cars/Cars-04-36.png",purple3 = "res/Cars/Cars-04-37.png",green4 = "res/Cars/Cars-04-38.png",orange3 = "res/Cars/Cars-04-39.png",brown4 = "res/Cars/Cars-04-40.png",peach2 = "res/Cars/Cars-04-41.png",red5 = "res/Cars/Cars-04-42.png",gray4 = "res/Cars/Cars-04-43.png",yellow5 = "res/Cars/Cars-04-44.png",blue5 = "res/Cars/Cars-04-45.png",green5 = "res/Cars/Cars-04-46.png",orange4 = "res/Cars/Cars-04-47.png",brown5 = "res/Cars/Cars-04-48.png";
    };

    // new keyword to deal with
    extern carColor carColors; // Declare carColors as an external instance
    extern std::string* colors[48]; // Declare colors as an external array
    
    std::string windowTitle = "Racing Game by Rafay & Salman";

    // background color
    sf::Color darkGreen = sf::Color(5, 128, 15); // dark green color darkGreen

}