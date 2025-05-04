#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <random>
#include <ctime>          // For std::time
#include <iostream>

#include "elements.hpp"
#include "keyControls.hpp"
#include "configuration.hpp"
#include "gameFunctions.hpp"

using namespace std;

//  DECLARATIONS
//-----------------------------------------------//
sf::Clock gameClock, scoreClock;// ;
///////////////////////////////////////////////////
//? Main game window
float WIDTH = conf::WindowWidth;
float HEIGHT = conf::WindowHeight;
sf::RenderWindow* window = nullptr;

///////////////////////////////////////////////////
//? declare road texture
sf::Texture roadTexture;


///////////////////////////////////////////////////
//? declare car texture
sf::Texture playerCarTexture[2];
sf::Texture NPCCarTextures[3];
///////////////////////////////////////////////////

///////////////////////////////////////////////////
//? declare road1 and road2 // constructor only called in loadStructures()
elements::background road1,road2,road3;
///////////////////////////////////////////////////
//? declare playerCar // constructor only called in loadPlayer()
elements::PlayerCar playerCar[2],NPCCars[3];
///////////////////////////////////////////////////
// define scroll speeds

float roadScrollSpeed = conf::playerCarSpeed[0]; // speed of the road
float NPCScrollSpeed[3] = {
    roadScrollSpeed - conf::NPCCarSpeed[0], 
    roadScrollSpeed - conf::NPCCarSpeed[1], 
    roadScrollSpeed - conf::NPCCarSpeed[2]
};


///////////////////////////////////////////////////
float roadScaledHeight;
float roadScaledWidth;
float roadLanes[2];

//-----------------------------------------------//

int loadStructures(){
    // Load road texture
    std::cout << "Loading road texture from: " << conf::road << std::endl;
    if (!roadTexture.loadFromFile(conf::road)) {
        std::cerr << "Failed to load road texture\n";
        return -1;
    }
    road1 = elements::background(roadTexture);
    road2 = elements::background(roadTexture);
    road3 = elements::background(roadTexture);
    // roadTexture.getSize().x is width of the road texture
    road1.setScale(conf::roadScale, conf::roadScale); // Scale if needed
    road2.setScale(conf::roadScale, conf::roadScale); // Scale if needed
    road3.setScale(conf::roadScale, conf::roadScale); // Scale if needed
    
    roadScaledHeight = roadTexture.getSize().y * road1.getScale().y;
    roadScaledWidth = roadTexture.getSize().x * road1.getScale().x;
    
    road1.setPosition((WIDTH-roadScaledWidth)/2, roadScaledHeight);
    road2.setPosition((WIDTH-roadScaledWidth)/2, 0);
    road3.setPosition((WIDTH-roadScaledWidth)/2, - 1*roadScaledHeight);
    

    roadLanes[0] = road1.getPosition().x;
    roadLanes[1] = road1.getPosition().x + roadScaledWidth;
    return 0;

}


int loadPlayers(){
    
    std::cout << "Loading player car texture: " << conf::carColors[3] << std::endl;
    if (!playerCarTexture[0].loadFromFile(conf::carColors[1])) {
        std::cerr << "Failed to load player texture\n";
        return -1;
    }
    playerCar[0] = elements::PlayerCar(playerCarTexture[0]);
    playerCar[0].topSpeed = conf::playerCarTopSpeed; // Set the top speed of the player car
    playerCar[0].setScale(conf::CarsScale, conf::CarsScale); // Scale if needed
    playerCar[0].setPosition(conf::Pcar1Pos.x, conf::Pcar1Pos.y); // Center near bottom
    
    //////////////////////////////////////////////////////////////
    
    if (!playerCarTexture[1].loadFromFile(conf::carColors[8])) {
        std::cerr << "Failed to load player texture\n";
        return -1;
    }
    
    playerCar[1] = elements::PlayerCar(playerCarTexture[1]);
    playerCar[1].topSpeed = conf::playerCarTopSpeed; // Set the top speed of the player car
    playerCar[1].setScale(conf::CarsScale, conf::CarsScale); // Scale if needed
    playerCar[1].setPosition(conf::Pcar2Pos.x, conf::Pcar2Pos.y); // Center near bottom
    
    return 0;
}


void moveBackground(float scrollSpeed,float deltaTime){
    road1.move(0, scrollSpeed * deltaTime);
    road2.move(0, scrollSpeed * deltaTime);
    road3.move(0, scrollSpeed * deltaTime);
    

    // width-roadTexture.getSize().x explanation:
    // for (width of the screen - width of the road) give us an offset
    // when centering, if we directly used width/2 the road position the road will look 'off' because the road's position is set from left side, (width- getsize.x)/2 gives us a better result, however (width- getsize.x) is too long and complex to follow
    if (road1.getPosition().y >= HEIGHT)
        road1.setPosition(static_cast<float>((WIDTH-roadScaledWidth)/2),static_cast<float>(road3.getPosition().y - roadScaledHeight));
    
    if (road2.getPosition().y >= HEIGHT)
        road2.setPosition(static_cast<float>((WIDTH-roadScaledWidth)/2),static_cast<float>(road1.getPosition().y - roadScaledHeight));
    
    if (road3.getPosition().y >= HEIGHT)
        road3.setPosition(static_cast<float>((WIDTH-roadScaledWidth)/2),static_cast<float>(road2.getPosition().y - roadScaledHeight));
}

// int roadLanes[2] = {404,540}; // road lanes for NPC cars

// specialized function loaded only once in main
int load_n_NPC(int n,int i){
    // if (!NPCCarTextures[i].loadFromFile(conf::carColors[n])) {
    //     std::cerr << "Failed to load NPC1 texture\n";
    //     return -1;
    // }
    if (
        load::loadNPC(
            NPCCars[i],
            NPCCarTextures[i], 
            conf::carColors,
            func::getRandomNumber(gameClock,0,47),
            conf::NPCcarPos[i].x,
            conf::NPCcarPos[i /* (i + 2) % 3 */].y /* - 200 */, // prevents overlapping of NPC cars // for for f(i) = (i + 2) % 3, f(0) = 2, f(1) = 0, f(2) = 1
            conf::CarsScale
        ) == -1) // reload the NPC car if it goes off screen
    {
        return -1;
    } else {
        return 0;
    }
    
}

void moveNPC(int index,float scrollSpeed, float deltaTime){
    
    NPCCars[index].move(0, scrollSpeed * deltaTime);
    if (NPCCars[index].getPosition().y > HEIGHT + 30){
        conf::NPCcarPos[index].x =  static_cast<int>(func::getRandomNumber(gameClock, roadLanes[0], roadLanes[1]));  // update the NPC car position
        conf::NPCcarPos[index].y -= static_cast<int>(func::getRandomNumber(gameClock, 0, 500));                      // update the NPC car position
        load_n_NPC(func::getRandomNumber(gameClock, 0, 47),index); // i the ith npc car being loaded
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
static int playerBounds(int playerIndex) {
    if (playerCar[playerIndex].getPosition().x < 0 || 
        playerCar[playerIndex].getPosition().x + 10 > WIDTH || 
        playerCar[playerIndex].getPosition().y < 0 || 
        playerCar[playerIndex].getPosition().y + 10 > HEIGHT) {
        
        // Nested clauses for specific boundaries and corners
        if (playerCar[playerIndex].getPosition().x < 0 && playerCar[playerIndex].getPosition().y < 0) {
            return 1; // Top-left corner
        } else if (playerCar[playerIndex].getPosition().y < 0 && playerCar[playerIndex].getPosition().x + 10 > WIDTH) {
            return 3; // Top-right corner
        } else if (playerCar[playerIndex].getPosition().x < 0 && playerCar[playerIndex].getPosition().y + 10 > HEIGHT) {
            return 0; // Bottom-left corner
        } else if (playerCar[playerIndex].getPosition().x + 10 > WIDTH && playerCar[playerIndex].getPosition().y + 10 > HEIGHT) {
            return 0; // Bottom-right corner
        } else if (playerCar[playerIndex].getPosition().y < 0) {
            return 2; // Top boundary
        } else if (playerCar[playerIndex].getPosition().x < 0) {
            return 4; // Left boundary
        } else if (playerCar[playerIndex].getPosition().x + 10 > WIDTH) {
            return 6; // Right boundary
        } else if (playerCar[playerIndex].getPosition().y + 10 > HEIGHT) {
            return 0; // Bottom boundary
        }
        return 0;
    } else {
        // No boundary reached
        return 0;
    }
}
// left -1, right 1, no collision 0
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

int playerCollisionDirectionAnyNPC(int playerIndex){

    for (size_t i = 0; i < 3; i++)
    {
        if (collision(playerCar[playerIndex], NPCCars[i])) {                 // Collision occurred
            return collisionDirection(playerCar[playerIndex], NPCCars[i]);   // Return the collision direction
        }
    }
    return 0; // No collision
}


// // all collisions
// bool playerCollision(){

//     for (size_t i = 0; i < 3; i++)
//     {
//         if (collision(playerCar, NPCCars[i])) {
//             return true; // Collision occurred
//         }
//     }
//     return false; // No collision
// }

// defines all movements done by the player car, whether they are controlled by player or the environment
void movePlayer(float dT, float speedVert, float speedHorz) {
    int bounds1 = playerBounds(0); // get the player bounds
    int bounds2 = playerBounds(1); // get the player bounds

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!
    // !!!! PLAYER 1 MOVEMENT !!!!
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!
    // car will roll down if it is off the road
    if (
        !collision(road1,playerCar[0]) && 
        !collision(road2,playerCar[0]) &&
        !collision(road3,playerCar[0])
    )
    {
        playerCar[0].moveDown(dT,conf::Drag); // move down with the road if collision occurs
    }
    

    for (size_t i = 0; i < 3; i++)
    {
        // player will down with the NPC car if they collide
        if (collision(playerCar[0], NPCCars[i]))
        {
            playerCar[0].moveDown(dT, conf::NPCCarSpeed[i]); // move down WITH the NPC1 Car if collision occurs
        }
    }
    if (playerCollisionDirectionAnyNPC(0)== -1)
    {
        playerCar[0].moveRight(dT, 20); // move right if collision occurs
    } else if (playerCollisionDirectionAnyNPC(0)== 1)
    {
        playerCar[0].moveLeft(dT, 20); // move left  if collision occurs
    }
    
    
    
    // Left movement (only if the player is not at the left boundary)
    if (
        key::pressedLeft()   && 
        bounds1 != 1 && 
        bounds1 != 4 && 
        bounds1 != 7 && 
        (playerCollisionDirectionAnyNPC(0)!=-1) 
    )
    {
        playerCar[0].moveLeft(dT, speedHorz);
    }
    
    // Right movement (only if the player is not at the right boundary)
    if (
        key::pressedRight()  && 
        bounds1 != 3 && 
        bounds1 != 6 && 
        bounds1 != 9 && 
        (playerCollisionDirectionAnyNPC(0)!= 1) 
    )
    {
        playerCar[0].moveRight(dT, speedHorz);
    }
        
        // Up movement (only if the player is not at the top boundary)
    if (key::pressedUp()     && 
        bounds1 != 1 && 
        bounds1 != 2 && 
        bounds1 != 3 && 
        !collision(playerCar[0], NPCCars[0]) && 
        !collision(playerCar[0], NPCCars[1]) && 
        !collision(playerCar[0], NPCCars[2])
    )
    {
        playerCar[0].moveUp(dT, speedVert);
    }
    
    // Down movement (only if the player is not at the bottom boundary)
    if (
        key::pressedDown()   && 
        bounds1 != 7 && 
        bounds1 != 8 && 
        bounds1 != 9
    )
    {
        playerCar[0].moveDown(dT, speedVert);
    }
    
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!
    // !!!! PLAYER 2 MOVEMENT !!!!
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!

    // car will roll down if it is off the road
    if (
        !collision(road1,playerCar[1]) && 
        !collision(road2,playerCar[1]) &&
        !collision(road3,playerCar[1])
    )
    {
        playerCar[1].moveDown(dT,conf::Drag); // move down with the road if collision occurs
    }
    

    for (size_t i = 0; i < 3; i++)
    {
        // player will down with the NPC car if they collide
        if (
            collision(playerCar[1], NPCCars[i])
        )
        {
            playerCar[1].moveDown(dT, conf::NPCCarSpeed[i]); // move down WITH the NPC1 Car if collision occurs
        }
    }
    if (
        playerCollisionDirectionAnyNPC(0)== -1
    )
    {
        playerCar[1].moveRight(dT, 20); // move right if collision occurs
    } 
    else if (
        playerCollisionDirectionAnyNPC(0)== 1
    )
    {
        playerCar[1].moveLeft(dT, 20); // move left  if collision occurs
    }

    // Left movement (only if the player is not at the left boundary)
    if (
        key::pressedA() && 
        bounds2 != 1    && 
        bounds2 != 4    && 
        bounds2 != 7    && 
        (playerCollisionDirectionAnyNPC(1)!=-1) 
    )
    playerCar[1].moveLeft(dT, speedHorz);
    
    // Right movement (only if the player is not at the right boundary)
    if (
        key::pressedD() && 
        bounds2 != 3    && 
        bounds2 != 6    && 
        bounds2 != 9    && 
        (playerCollisionDirectionAnyNPC(1)!= 1 ) 
    )
    {
        playerCar[1].moveRight(dT, speedHorz);
    }
        
    // Up movement (only if the player is not at the top boundary)
    if (
        key::pressedW() && 
        bounds2 != 1    && 
        bounds2 != 2    && 
        bounds2 != 3    && 
        !collision(playerCar[1], NPCCars[0]) && 
        !collision(playerCar[1], NPCCars[1]) && 
        !collision(playerCar[1], NPCCars[2])
    )
    {
        playerCar[1].moveUp(dT, speedVert);
    }
    
    // Down movement (only if the player is not at the bottom boundary)
    if (
        key::pressedS() && 
        bounds2 != 7    && 
        bounds2 != 8    && 
        bounds2 != 9
    )
    {
        playerCar[1].moveDown(dT, speedVert);
    }
}

// move cursor up
void cursorUp(int X){
    printf("\033[%dA",X); // Move up X lines;
}

void hideCursor() {
    std::cout << "\033[?25l"; // ANSI escape code to hide the cursor
}

void debugInfo(sf::Clock clock){
        cursorUp(22);

        // Print information in a readable format
        for (size_t i = 0; i < 51; i++)
        {
            cout << "=";
        }
        cout<<endl;
        cout << "Screen res:           " << WIDTH << ", " << HEIGHT << "\n";
        cout << "FPS:                  " << 1.f / clock.restart().asSeconds() << "\n";
        cout << "Player1 Car Position: " << playerCar[0].getPosition().x << ", " << playerCar[0].getPosition().y << "\n";
        cout << "Player2 Car Position: " << playerCar[1].getPosition().x << ", " << playerCar[1].getPosition().y << "\n";
        cout << "NPC1 Car Position:    " << NPCCars[0].getPosition().x << ", " << NPCCars[0].getPosition().y << "\n";
        cout << "NPC2 Car Position:    " << NPCCars[1].getPosition().x << ", " << NPCCars[1].getPosition().y << "\n";
        cout << "NPC3 Car Position:    " << NPCCars[2].getPosition().x << ", " << NPCCars[2].getPosition().y << "\n";
        cout << "Road1 Position:       " << road1.getPosition().x << ", " << road1.getPosition().y << "\n";
        cout << "Road2 Position:       " << road2.getPosition().x << ", " << road2.getPosition().y << "\n";
        cout << "Road3 Position:       " << road3.getPosition().x << ", " << road3.getPosition().y << "\n";
        cout << "Road speed:           " << roadScrollSpeed << "\n";
        cout << "Road lanes:           " << roadLanes[0] <<" , "<<roadLanes[1]<<" , "<< roadScaledHeight<<" , "<< roadScaledWidth<<"\n";
        cout << "Player1 Car Scale:    " << playerCar[0].getScale().x << ", " << playerCar[0].getScale().y << "\n";
        cout << "Player2 Car Scale:    " << playerCar[1].getScale().x << ", " << playerCar[1].getScale().y << "\n";
        cout << "Player speed:         " << conf::playerCarSpeed[0] << " npc1 speed: " /* << right */ << NPCScrollSpeed[0] << " npc2 speed: " /* << right */ << NPCScrollSpeed[1] << " npc3 speed: " /* << right */ << NPCScrollSpeed[2] << "\n";
        cout << "Road dimensions:      " << roadTexture.getSize().x << ", " << roadTexture.getSize().y << "\n";
        cout << "Bound1:               " << playerBounds(0) << "\n";
        cout << "Bound2:               " << playerBounds(1) << "\n";
        // cout << "Collision npc1:       " << collision(playerCar,NPCCars[0]) << "\n";
        // cout << "Collision npc2:       " << collision(playerCar,NPCCars[1]) << "\n";
        // cout << "Collision npc3:       " << collision(playerCar,NPCCars[2]) << "\n";
        cout << "Car1 W x H:            " << playerCar[0].getGlobalBounds().width << ", " << playerCar[0].getGlobalBounds().height << endl;
        cout << "Car2 W x H:            " << playerCar[1].getGlobalBounds().width << ", " << playerCar[1].getGlobalBounds().height << endl;
        // cout /* << left << setw(30) */ << "rand, rl1, rl2, size: " /* << right */ << getRandomNumber(gameClock, roadLanes[0], roadLanes[1]) << ", " << roadLanes[0] << ", " << roadLanes[1] << ", " << roadTexture.getSize().x << endl;
        
        for (size_t i = 0; i < 51; i++)
        {
            cout << "=";
        }
        cout<<endl;
}

void gameStep(float dT){

        // func::getRandomNumber(gameClock, 0, 1); // update the random number generator

        float roadScrollSpeed = conf::playerCarSpeed[0]; // redefine road scroll speed as player car speed is also being redefined
        // hence the npc speeds are also redefined
        for (size_t i = 0; i < 3; i++)
        {
            NPCScrollSpeed[i] = roadScrollSpeed - conf::NPCCarSpeed[i] ; // redefine the npc speeds
        }

        // !!!!!!!!!!!!!!!!!!!!!!!!!!!
        // !!!! PLAYER 1 MOVEMENT !!!!
        // !!!!!!!!!!!!!!!!!!!!!!!!!!!
        // increasing acceleration on press up
        if (key::pressedUp()) {
            conf::playerCarSpeed[0] += 5; // increase the acceleration of the road 
        } else if (key::pressedDown() && conf::playerCarSpeed[0] > 0) {
            conf::playerCarSpeed[0] -= 5; // decrease the acceleration of the road 
        } else
        // only speed up until top speed is reached
        if (playerCar[0].topSpeed > conf::playerCarSpeed[0]) {
            conf::playerCarSpeed[0] += conf::playerCarAcceleration * dT; // increase the speed of the road // v = u + a*dt
        }
        // !!!!!!!!!!!!!!!!!!!!!!!!!!!
        // !!!! PLAYER 2 MOVEMENT !!!!
        // !!!!!!!!!!!!!!!!!!!!!!!!!!!
        // increasing acceleration on press up
        if (key::pressedW()) {
            conf::playerCarSpeed[1] += 5; // increase the acceleration of the road 
        } else if (key::pressedS() && conf::playerCarSpeed[1] > 0) {
            conf::playerCarSpeed[1] -= 5; // decrease the acceleration of the road 
        } else
        // only speed up until top speed is reached
        if (playerCar[1].topSpeed > conf::playerCarSpeed[1]) {
            conf::playerCarSpeed[1] += conf::playerCarAcceleration * dT; // increase the speed of the road // v = u + a*dt
        }

        //? Scroll road background
        moveBackground(roadScrollSpeed,dT);
        
        //? Scroll NPCs background
        for (size_t i = 0; i < 3; i++)
        {
            moveNPC(i,NPCScrollSpeed[i], dT);
        }

        //? Player car movement (basic)
        movePlayer(dT, conf::swerveVert,conf::swerveHorz); // this is the speed with which the player cars moves ACROSS the screen
}

void renderGameElements(){
    // order of render determines the position of the elements
    window->clear(conf::darkGreen);
    window->draw(road1);
    window->draw(road2);
    window->draw(road3);
    window->draw(playerCar[0]);
    window->draw(playerCar[1]);
    for (size_t i = 0; i < 3; i++)
    {
        window->draw(NPCCars[i]);
    }
    window->display();
}

int playGame(float deltaTime, int i) {
    time_t game_start = time(NULL);
    time_t game_end = time(NULL);
    debugInfo(gameClock);
    // if(i==0){
    //     i = 100;
    // }
    // i--;
    if (
        playerCar[0].getPosition().y < HEIGHT &&
        playerCar[1].getPosition().y < HEIGHT
    ) {
        //? runs the simulation, all game events, like car/npc/road - movement/behaviour,
        gameStep(deltaTime);
        //? final rendering of all GAME elements to screen
        renderGameElements();
    } else {
        game_end = time(NULL);
    }
    return game_end - game_start; // return the time survived
}

void initWindowEvents(){
    // init window close on close button
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();
    }
    // close program by pressing ESC
    if (key::pressedESC()) {
        window->close();
    }
}

int main() {
    std::cout << "Starting program...\n";

    hideCursor();
    std::cout << "Creating window...\n";
    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), conf::windowTitle);
    
    std::cout << "Loading resources...\n";
    if (
        // order of loading determines the order of rendering
        loadStructures()  == -1
        ||load_n_NPC(0,0) == -1
        ||load_n_NPC(3,1) == -1
        ||load_n_NPC(2,2) == -1
        ||loadPlayers()   == -1
    ) {
        std::cerr << "Failed to load resources\n";
        return -1;
    }
    
    system("cls"); // clear the console

    int i = 100;

    int score = 0;
    // Main game loop
    while (window->isOpen() && score == 0 ) {
        initWindowEvents();

        
        
        float deltaTime = gameClock.restart().asSeconds();
        score = playGame(deltaTime,i);
        
        // show info every thousandth frame
        cout<<"score: "<<score<<"\n";
        cursorUp(1);

    }
    cout<<"score: "<<score<<"\n";

    cout << "Exiting program...\n";
    return 0;
}
