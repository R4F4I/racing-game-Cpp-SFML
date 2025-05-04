#pragma once
 
#include <iostream>
 
namespace conf
 
{
    float WindowWidth = 800;
    float WindowHeight = 970;

    struct position{
        float x,y;
    };
    
    struct position WindowCenter = {WindowWidth/2,WindowHeight/2};
    struct position Pcar1Pos = {375.f,500.f};
    struct position Pcar2Pos = {275.f,500.f};
    struct position NPCcarPos[3]  = {
        {404.f, 300.f},    // NPC1CarPosition
        {404.f, -1700.f},  // NPC2CarPosition
        {504.f, -1000.f}   // NPC3CarPosition
    };

    ///////////////////////////
    // car speed vs scroll speed
    // car speed will be the representative speed, it will show whether the speed of the car
    // ! DO NOT USE THESE VALUES DIRECTLY IN MAIN
    // Representative speeds
    float playerCarSpeed[2] = {1.f,1.f};       // Initial player cars speed
    float playerCarTopSpeed = 1200.f; // Maximum player car speed
    float playerCarAcceleration = 5.f; // Acceleration of the player car
    float NPCCarSpeed[3] = {380.f, 180.f, 280.f}; // Representative speeds for NPC cars
    // Swerve speeds for player movement
    float swerveVert = 250.f; // Vertical movement speed
    float swerveHorz = 250.f; // Horizontal movement speed
    // Drag (when off-road)
    float Drag = 200.f;
    // Road lanes for NPC cars
    // int roadLanes[2] = {404, 540};
    ///////////////////////////

    float roadScale = 0.4f;
    float CarsScale = 0.6f;

    std::string road = "D:/rafay/racing-game-Cpp-SFML/res/road.png";
    std::string carColors[48] = {
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-01.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-02.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-03.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-04.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-05.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-06.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-07.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-08.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-09.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-10.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-11.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-12.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-13.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-14.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-15.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-16.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-17.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-18.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-19.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-20.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-21.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-22.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-23.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-24.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-25.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-26.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-27.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-28.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-29.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-30.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-31.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-32.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-33.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-34.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-35.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-36.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-37.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-38.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-39.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-40.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-41.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-42.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-43.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-44.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-45.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-46.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-47.png",
        "D:/rafay/racing-game-Cpp-SFML/res/Cars/Cars-04-48.png"};
    std::string windowTitle = "Racing Game by Rafay & Salman";

    sf::Color darkGreen = sf::Color(5, 128, 15); // dark green color darkGreen

}