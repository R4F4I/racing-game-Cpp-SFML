#pragma once
 
#include <iostream>
 
namespace conf
 
{
    float width = 1000;
    float height = 499;

    struct position{
        float x,y;
    };
    
    struct position center = {width/2,height/2};
    struct position PcarPos = {375.f,300.f};
    struct position NPCcarPos[3]  = {
        {404.f, 300.f},    // NPC1CarPosition
        {404.f, -1700.f},  // NPC2CarPosition
        {504.f, -1000.f}   // NPC3CarPosition
    };

    // struct center
    // {
    //     int x=width/2,y=height/2;
    // };

    // struct playerCarPosition
    // {
    //     int x=375,y=300;
    // };
    // struct NPC1CarPosition
    // {
    //     int x=404,y=300;
    // };
    // struct NPC2CarPosition
    // {
    //     int x=404,y=-1700;
    // };
    // struct NPC3CarPosition
    // {
    //     int x=504,y=-1000;
    // };
    
    // speed with which the car will roll down if it went off road
    float Drag = 200;
    
    
    

    
    ///////////////////////////
    // car speed vs scroll speed
    // car speed will be the representative speed, it will show whether the speed of the car
    // ! DO NOT USE THESE VALUES DIRECTLY IN MAIN
    float playerCarSpeed = 1.f;
    float playerCarTopSpeed = 600.f;
    float playerCarAcceleration = 5.f;
    float roadAcceleration = playerCarAcceleration;
    float NPCCarSpeed[3] = {380.f,180.f,280.f};
    // float NPC1CarSpeed = 380.f;
    // float NPC2CarSpeed = 180.f;
    // float NPC3CarSpeed = 280.f;
    
    // scroll speed is the actual acting speed used in the game
    // it will be used to scroll the road and the cars
    float roadScrollSpeed = playerCarSpeed;
    float NPCScrollSpeed[3] = {
        roadScrollSpeed - NPCCarSpeed[0], 
        roadScrollSpeed - NPCCarSpeed[1], 
        roadScrollSpeed - NPCCarSpeed[2]
    };
    // float NPC1ScrollSpeed = roadScrollSpeed - NPC1CarSpeed; // should this be redefined in main ?
    // float NPC2ScrollSpeed = roadScrollSpeed - NPC2CarSpeed; // should this be redefined in main ?
    // float NPC3ScrollSpeed = roadScrollSpeed - NPC3CarSpeed; // should this be redefined in main ?
    float playerScrollSpeed = roadScrollSpeed - playerCarSpeed; // is 0,
    ///////////////////////////




    float CarsScale = 0.6f;

    std::string road = "res/road.png";
    
    std::string carColors[48] = { 
        "res/Cars/Cars-04-01.png",
        "res/Cars/Cars-04-02.png",
        "res/Cars/Cars-04-03.png",
        "res/Cars/Cars-04-04.png",
        "res/Cars/Cars-04-05.png",
        "res/Cars/Cars-04-06.png",
        "res/Cars/Cars-04-07.png",
        "res/Cars/Cars-04-08.png",
        "res/Cars/Cars-04-09.png",
        "res/Cars/Cars-04-10.png",
        "res/Cars/Cars-04-11.png",
        "res/Cars/Cars-04-12.png",
        "res/Cars/Cars-04-13.png",
        "res/Cars/Cars-04-14.png",
        "res/Cars/Cars-04-15.png",
        "res/Cars/Cars-04-16.png",
        "res/Cars/Cars-04-17.png",
        "res/Cars/Cars-04-18.png",
        "res/Cars/Cars-04-19.png",
        "res/Cars/Cars-04-20.png",
        "res/Cars/Cars-04-21.png",
        "res/Cars/Cars-04-22.png",
        "res/Cars/Cars-04-23.png",
        "res/Cars/Cars-04-24.png",
        "res/Cars/Cars-04-25.png",
        "res/Cars/Cars-04-26.png",
        "res/Cars/Cars-04-27.png",
        "res/Cars/Cars-04-28.png",
        "res/Cars/Cars-04-29.png",
        "res/Cars/Cars-04-30.png",
        "res/Cars/Cars-04-31.png",
        "res/Cars/Cars-04-32.png",
        "res/Cars/Cars-04-33.png",
        "res/Cars/Cars-04-34.png",
        "res/Cars/Cars-04-35.png",
        "res/Cars/Cars-04-36.png",
        "res/Cars/Cars-04-37.png",
        "res/Cars/Cars-04-38.png",
        "res/Cars/Cars-04-39.png",
        "res/Cars/Cars-04-40.png",
        "res/Cars/Cars-04-41.png",
        "res/Cars/Cars-04-42.png",
        "res/Cars/Cars-04-43.png",
        "res/Cars/Cars-04-44.png",
        "res/Cars/Cars-04-45.png",
        "res/Cars/Cars-04-46.png",
        "res/Cars/Cars-04-47.png",
        "res/Cars/Cars-04-48.png"
    };

    /* // new keyword to deal with
    extern carColor carColors; // Declare carColors as an external instance
    extern std::string* colors[48]; // Declare colors as an external array */

    
    
    std::string windowTitle = "Racing Game by Rafay & Salman";

    // background color
    sf::Color darkGreen = sf::Color(5, 128, 15); // dark green color darkGreen

}