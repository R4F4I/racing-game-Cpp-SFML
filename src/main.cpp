#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <random>
#include <ctime>          // For std::time
#include <iostream>
#include <iomanip>  // <- Required for std::setw

#include "elements.hpp"
#include "keyControls.hpp"
#include "configuration.hpp"
#include "gameFunctions.hpp"

using namespace std;

//  DECLARATIONS
//-----------------------------------------------//
sf::Clock gameClock;
///////////////////////////////////////////////////
//? Main game window
float width = conf::width;
float height = conf::height;
sf::RenderWindow window(sf::VideoMode(width, height), conf::windowTitle);

///////////////////////////////////////////////////
//? declare road texture
sf::Texture roadTexture;


///////////////////////////////////////////////////
//? declare car texture
sf::Texture playerCarTexture;
sf::Texture NPCCarTextures[3];
///////////////////////////////////////////////////

///////////////////////////////////////////////////
//? declare road1 and road2 // constructor only called in loadStructures()
elements::background road1;
elements::background road2;
///////////////////////////////////////////////////
//? declare playerCar // constructor only called in loadPlayer()
elements::PlayerCar playerCar;
elements::PlayerCar NPCCars[3];
///////////////////////////////////////////////////

///////////////////////////////////////////////////


//assign speeds
void valueSetter(){
    // Set the speed of the player car and NPC car
    playerCar.speed = conf::playerCarSpeed;
    NPCCars[0].speed = conf::NPCCarSpeed[0];
    NPCCars[1].speed = conf::NPCCarSpeed[1];
    NPCCars[2].speed = conf::NPCCarSpeed[2];
}

//-----------------------------------------------//

int loadStructures(){
    // Load road texture
    if (!roadTexture.loadFromFile(conf::road)) {
        std::cerr << "Failed to load road.png\n";
        return -1;
    }


    road1 = elements::background(roadTexture);
    road2 = elements::background(roadTexture);

    
    // roadTexture.getSize().x is width of the road texture
    road1.setPosition((width-roadTexture.getSize().x)/2, 0);
    road2.setPosition((width-roadTexture.getSize().x)/2, -roadTexture.getSize().y);

    return 0;

}



int loadPlayer(){
    
    std::cout << "Loading player car texture: " << conf::carColors[3] << std::endl;
    if (!playerCarTexture.loadFromFile(conf::carColors[3])) {
        std::cerr << "Failed to load player texture\n";
        return -1;
    }
    
    playerCar = elements::PlayerCar(playerCarTexture);
    playerCar.topSpeed = conf::playerCarTopSpeed; // Set the top speed of the player car

    playerCar.setScale(conf::CarsScale, conf::CarsScale); // Scale if needed
    playerCar.setPosition(conf::PcarPos.x, conf::PcarPos.y); // Center near bottom
    
    return 0;
}


void moveBackground(float scrollSpeed,float deltaTime){
    road1.move(0, scrollSpeed * deltaTime);
    road2.move(0, scrollSpeed * deltaTime);
    
    // width-roadTexture.getSize().x explanation:
    // for (width of the screen - width of the road) give us an offset
    // when centering, if we directly used width/2 the road position the road will look 'off' because the road's position is set from left side, (width- getsize.x)/2 gives us a better result, however (width- getsize.x) is too long and complex to follow
    if (road1.getPosition().y >= roadTexture.getSize().y)
        road1.setPosition(static_cast<float>((width-roadTexture.getSize().x)/2),static_cast<float>(road2.getPosition().y - roadTexture.getSize().y));
    
    if (road2.getPosition().y >= roadTexture.getSize().y)
        road2.setPosition(static_cast<float>((width-roadTexture.getSize().x)/2),static_cast<float>( road1.getPosition().y - roadTexture.getSize().y));
}

int roadLanes[2] = {404,540}; // road lanes for NPC cars

// specialized function loaded only once in main
int load_n_NPC(int n,int i){
    if (!NPCCarTextures[i].loadFromFile(conf::carColors[n])) {
        std::cerr << "Failed to load NPC1 texture\n";
        return -1;
    }
    if (
        load::loadNPC(
            NPCCars[i],
            NPCCarTextures[i], 
            conf::carColors,
            func::getRandomNumber(gameClock,0,47),
            conf::NPCcarPos[i].x,
            conf::NPCcarPos[(i + 2) % 3].y - 200, // prevents overlapping of NPC cars // for for f(i) = (i + 2) % 3, f(0) = 2, f(1) = 0, f(2) = 1
            conf::CarsScale
        ) == -1) // reload the NPC car if it goes off screen
    {
        return -1;
    } else {
        return 0;
    }
    
}

void moveNPCs(float scrollSpeed1,float scrollSpeed2, float deltaTime){
    int rand = 0;
    for (size_t i = 0; i < 3; i++){
        NPCCars[i].move(0, scrollSpeed1 * deltaTime);
        if (NPCCars[i].getPosition().y > height + 30){
            rand = func::getRandomNumber(gameClock, roadLanes[0], roadLanes[1]);
            conf::NPCcarPos[i].x = rand;                                                 // update the NPC car position
            conf::NPCcarPos[i].y -= static_cast<int>(func::getRandomNumber(gameClock, 0, 500)); // update the NPC car position
            load_n_NPC(func::getRandomNumber(gameClock, 0, 47),i); // i the ith npc car being loaded
        }
    }
}


// the function returns 
//  1 2 3 
//  4 0 6
//  7 8 9
//  1: x<0      && y<0
//  2: y<0 
//  3: y<0      && x>width
//  4: x<0
//  6: x>width
//  7: x<0      && y>height
//  8: y>height
//  9: x>width  && y>height
//  for the following boundaries
//  note: since the function can only return one value at a time, it is not possible to check for multiple boundaries at once hence we function can determine whether the player is at a corner
//  or not. for this the corner cases have to be explicitly defined
static int playerBounds() {
    if (playerCar.getPosition().x < 0 || playerCar.getPosition().x + 10 > width || playerCar.getPosition().y < 0 || playerCar.getPosition().y + 10 > height) {
        // Nested clauses for specific boundaries and corners
        if (playerCar.getPosition().x < 0 && playerCar.getPosition().y < 0) {
            return 1; // Top-left corner
        } else if (playerCar.getPosition().y < 0 && playerCar.getPosition().x + 10 > width) {
            return 3; // Top-right corner
        } else if (playerCar.getPosition().x < 0 && playerCar.getPosition().y + 10 > height) {
            return 0; //7; // Bottom-left corner
        } else if (playerCar.getPosition().x + 10 > width && playerCar.getPosition().y + 10 > height) {
            return 0; //9; // Bottom-right corner
        } else if (playerCar.getPosition().y < 0) {
            return 2; // Top boundary
        } else if (playerCar.getPosition().x < 0) {
            return 4; // Left boundary
        } else if (playerCar.getPosition().x + 10 > width) {
            return 6; // Right boundary
        } else if (playerCar.getPosition().y + 10 > height) {
            return 0; //8; // Bottom boundary
        }
        return 0;
    } else {
        // No boundary reached
        return 0;
    }

}

int collisionDirection(sf::Sprite& player, sf::Sprite& npc) {
    if (player.getGlobalBounds().intersects(npc.getGlobalBounds())) {
        if (player.getPosition().x < npc.getPosition().x) {
            return -1; // Collision from the left
        } else if (player.getPosition().x > npc.getPosition().x) {
            return 1; // Collision from the right
        }
    }
    return 0; // No collision
}

bool collision(sf::Sprite& s1, sf::Sprite& s2) {
    return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}

int playerCollisionDirectionAnyNPC(){

    for (size_t i = 0; i < 3; i++)
    {
        if (collision(playerCar, NPCCars[i])) {                 // Collision occurred
            return collisionDirection(playerCar, NPCCars[i]);   // Return the collision direction
        }
    }
    return 0; // No collision
}


// all collisions
bool playerCollision(){

    for (size_t i = 0; i < 3; i++)
    {
        if (collision(playerCar, NPCCars[i])) {
            return true; // Collision occurred
        }
    }
    return false; // No collision
}

// defines all movements done by the player car, whether they are controlled by player or the environment
void movePlayer(float dT, float speedVert, float speedHorz){
    int bounds = playerBounds();

    // car will roll down if it is off the road
    if (!collision(road1,playerCar) && !collision(road2,playerCar))
    {
        playerCar.moveDown(dT,conf::Drag); // move down with the road if collision occurs
    }
    

    for (size_t i = 0; i < 3; i++)
    {
        // player will down with the NPC car if they collide
        if (collision(playerCar, NPCCars[i]))
        {
            playerCar.moveDown(dT, conf::NPCCarSpeed[i]); // move down WITH the NPC1 Car if collision occurs
        }
    }

    // Left movement (only if the player is not at the left boundary)
    if (key::pressedLeft()   && bounds != 1 && bounds != 4 && bounds != 7 && (playerCollisionDirectionAnyNPC()!=-1) )
        playerCar.moveLeft(dT, speedHorz);

    // Right movement (only if the player is not at the right boundary)
    if (key::pressedRight()  && bounds != 3 && bounds != 6 && bounds != 9&& (playerCollisionDirectionAnyNPC()!= 1 ) )
        playerCar.moveRight(dT, speedHorz);

    // Up movement (only if the player is not at the top boundary)
    if (key::pressedUp()     && 
            bounds != 1 && 
            bounds != 2 && 
            bounds != 3 && 
            !collision(playerCar, NPCCars[0]) && 
            !collision(playerCar, NPCCars[1]) && 
            !collision(playerCar, NPCCars[2])
        )
        playerCar.moveUp(dT, speedVert);

    // Down movement (only if the player is not at the bottom boundary)
    if (key::pressedDown()   && bounds != 7 && bounds != 8 && bounds != 9)
        playerCar.moveDown(dT, speedVert);
}

// move cursor up
void cursorUp(int X){
    printf("\033[%dA",X); // Move up X lines;
}

void hideCursor() {
    std::cout << "\033[?25l"; // ANSI escape code to hide the cursor
}

void debugInfo(sf::Clock clock){
        cursorUp(18);

        // Print information in a readable format
        for (size_t i = 0; i < 51; i++)
        {
            cout << "=";
        }
        cout<<endl;
        cout /* << left << setw(30) */ << "Screen res:           " /* << right */ << width << ", " << height << "\n";
        cout /* << left << setw(30) */ << "FPS:                  " /* << right */ << 1.f / clock.restart().asSeconds() << "\n";
        cout /* << left << setw(30) */ << "Player Car Position:  " /* << right */ << playerCar.getPosition().x << ", " << playerCar.getPosition().y << "\n";
        cout /* << left << setw(30) */ << "NPC1 Car Position:    " /* << right */ << NPCCars[0].getPosition().x << ", " << NPCCars[0].getPosition().y << "\n";
        cout /* << left << setw(30) */ << "NPC2 Car Position:    " /* << right */ << NPCCars[1].getPosition().x << ", " << NPCCars[1].getPosition().y << "\n";
        cout /* << left << setw(30) */ << "NPC3 Car Position:    " /* << right */ << NPCCars[2].getPosition().x << ", " << NPCCars[2].getPosition().y << "\n";
        cout /* << left << setw(30) */ << "Road1 Position:       " /* << right */ << road1.getPosition().x << ", " << road1.getPosition().y << "\n";
        cout /* << left << setw(30) */ << "Road2 Position:       " /* << right */ << road2.getPosition().x << ", " << road2.getPosition().y << "\n";
        cout /* << left << setw(30) */ << "Player Car Scale:     " /* << right */ << playerCar.getScale().x << ", " << playerCar.getScale().y << "\n";
        cout /* << left << setw(30) */ << "Player speed:         " /* << right */ << conf::playerCarSpeed << "\n";
        cout /* << left << setw(30) */ << "Road dimensions:      " /* << right */ << roadTexture.getSize().x << ", " << roadTexture.getSize().y << "\n";
        cout /* << left << setw(30) */ << "Bound:                " /* << right */ << playerBounds() << "\n";
        cout /* << left << setw(30) */ << "Collision npc1:       " /* << right */ << collision(playerCar,NPCCars[0]) << "\n";
        cout /* << left << setw(30) */ << "Collision npc2:       " /* << right */ << collision(playerCar,NPCCars[1]) << "\n";
        cout /* << left << setw(30) */ << "Collision npc3:       " /* << right */ << collision(playerCar,NPCCars[2]) << "\n";
        cout /* << left << setw(30) */ << "Car W x H:            " /* << right */ << playerCar.getGlobalBounds().width << ", " << playerCar.getGlobalBounds().height << endl;
        // cout /* << left << setw(30) */ << "rand, rl1, rl2, size: " /* << right */ << getRandomNumber(gameClock, roadLanes[0], roadLanes[1]) << ", " << roadLanes[0] << ", " << roadLanes[1] << ", " << roadTexture.getSize().x << endl;
        
        for (size_t i = 0; i < 51; i++)
        {
            cout << "=";
        }
        cout<<endl;
}

void gameStep(float dT){
    conf::NPCScrollSpeed[0] = conf::playerCarSpeed - conf::NPCCarSpeed[0]; // should this be redefined in main ?
    conf::NPCScrollSpeed[1] = conf::playerCarSpeed - conf::NPCCarSpeed[1]; // should this be redefined in main ?
    conf::NPCScrollSpeed[2] = conf::playerCarSpeed - conf::NPCCarSpeed[2]; // should this be redefined in main ?

        // increasing acceleration on press up
        if (key::pressedUp()) {
            conf::playerCarAcceleration += 20; // increase the acceleration of the road 
        } else if (key::pressedDown() && conf::playerCarSpeed > 0) {
            conf::playerCarAcceleration -= 20; // decrease the acceleration of the road 
        } else
        // only speed up until top speed is reached
        if (playerCar.topSpeed > conf::playerCarSpeed) {
            conf::playerCarSpeed += conf::playerCarAcceleration * dT; // increase the speed of the road 
        }

        //? Scroll road background
        moveBackground(conf::playerCarSpeed,dT);
        

        //? Scroll NPCs background
        moveNPCs(conf::NPCScrollSpeed[0],conf::NPCScrollSpeed[1], dT);


        //? Player car movement (basic)
        movePlayer(dT, 250,250); // this is the speed with which the player car ACROSS moves
}

void renderElements(){
    // order of render determines the position of the elements
    window.clear(conf::darkGreen);
    window.draw(road1);
    window.draw(road2);
    window.draw(playerCar);
    for (size_t i = 0; i < 3; i++)
    {
        window.draw(NPCCars[i]);
    }
    window.display();
}

void initWindowEvents(){
    // init window close on close button
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    // close program by pressing ESC
    if (key::pressedESC()) {
        window.close();
    }
}

int main() {
    hideCursor();
    // std::srand(static_cast<unsigned int>(std::time(nullptr))); // creating rand seed
    float roadScrollSpeed = conf::roadScrollSpeed;
    if (
        // order of loading determines the order of rendering
          load_n_NPC(0,0)  == -1
        ||load_n_NPC(3,1)  == -1
        ||load_n_NPC(2,2)  == -1
        ||loadPlayer()     == -1
        ||loadStructures() == -1
    ) {
        std::cerr << "Failed to load \n";
        return -1;
    }

    int i = 100;

    // Main game loop
    while (window.isOpen()) {
        // show info every thousandth frame
        if(i==0)
        {
            debugInfo(gameClock);
            i = 100;
        }
        i--;
        
        initWindowEvents();

        
        float deltaTime = gameClock.restart().asSeconds();

        gameStep(deltaTime);

        //? final rendering of all elements to screen
        renderElements();
    }
    
    // delete conf::colors[48];

    return 0;
}
