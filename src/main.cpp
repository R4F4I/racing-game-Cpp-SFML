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

using namespace std;

//  DECLARATIONS
//-----------------------------------------------//
sf::Clock gameClock;
///////////////////////////////////////////////////
//? Main game window
float width = conf::width;
float height = conf::height;
struct conf::playerCarPosition PcarPos;
struct conf::NPC1CarPosition NPC1carPos;
struct conf::NPC2CarPosition NPC2carPos;
sf::RenderWindow window(sf::VideoMode(width, height), conf::windowTitle);

///////////////////////////////////////////////////
//? declare road texture
sf::Texture roadTexture;


///////////////////////////////////////////////////
//? declare car texture
sf::Texture playerCarTexture;
sf::Texture NPC1CarTexture;
sf::Texture NPC2CarTexture;

namespace conf{
    carColor carColors;
    std::string* colors[48] = {&carColors.red1, &carColors.black1, &carColors.yellow1, &carColors.blue1, &carColors.purple1, &carColors.green1, &carColors.orange1, &carColors.brown1,&carColors.red2, &carColors.gray1, &carColors.cream, &carColors.blue2, &carColors.pink1, &carColors.lime, &carColors.white, &carColors.peach, &carColors.brown2,&carColors.darkgray, &carColors.yellow2, &carColors.navy, &carColors.purple2, &carColors.green2, &carColors.orange2, &carColors.black2, &carColors.red3,&carColors.brown3, &carColors.yellow3, &carColors.blue3, &carColors.pink2, &carColors.green3, &carColors.gray2, &carColors.beige, &carColors.red4, &carColors.gray3,&carColors.yellow4, &carColors.blue4, &carColors.purple3, &carColors.green4, &carColors.orange3, &carColors.brown4, &carColors.peach2, &carColors.red5,&carColors.gray4, &carColors.yellow5, &carColors.blue5, &carColors.green5, &carColors.orange4, &carColors.brown5};
}



///////////////////////////////////////////////////

///////////////////////////////////////////////////
//? declare road1 and road2 // constructor only called in loadStructures()
elements::background road1;
elements::background road2;
///////////////////////////////////////////////////
//? declare playerCar // constructor only called in loadPlayer()
elements::PlayerCar playerCar;
elements::PlayerCar NPC1Car;
elements::PlayerCar NPC2Car;
///////////////////////////////////////////////////

///////////////////////////////////////////////////

// rand gen
int getRandomNumber(sf::Clock& clock, int min = 0, int max = 47) {
    static std::random_device rd; // Non-deterministic seed
    static std::mt19937 engine(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<int> dist(min, max); // Uniform distribution
    return dist(engine); // Generate a random integer
}

//assign speeds
void valueSetter(){
    // Set the speed of the player car and NPC car
    playerCar.speed = conf::playerCarSpeed;
    NPC1Car.speed = conf::NPC1CarSpeed;
    NPC2Car.speed = conf::NPC2CarSpeed;
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
    
    std::cout << "Loading player car texture: " << conf::carColors.purple3 << std::endl;
    if (!playerCarTexture.loadFromFile(conf::carColors.purple3)) {
        std::cerr << "Failed to load player texture\n";
        return -1;
    }
    
    playerCar = elements::PlayerCar(playerCarTexture);
    playerCar.topSpeed = conf::playerCarTopSpeed; // Set the top speed of the player car

    playerCar.setScale(conf::CarsScale, conf::CarsScale); // Scale if needed
    playerCar.setPosition(PcarPos.x, PcarPos.y); // Center near bottom
    
    return 0;
}

int loadNPC(elements::PlayerCar& pc,sf::Texture& t, int carColorIndex,int x,int y){
    if (!t.loadFromFile(*conf::colors[carColorIndex])) {
        std::cerr << "Failed to load NPC texture\n";
        return -1;
    }
    
    pc = elements::PlayerCar(t);
    
    pc.setScale(static_cast<float>(conf::CarsScale), static_cast<float>(conf::CarsScale)); // Scale if needed
    pc.setPosition(x, y); // Center near bottom

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
    // road1.setPosition(width/2.5, road2.getPosition().y - roadTexture.getSize().y);
    if (road2.getPosition().y >= roadTexture.getSize().y)
    road2.setPosition(static_cast<float>((width-roadTexture.getSize().x)/2),static_cast<float>( road1.getPosition().y - roadTexture.getSize().y));
    // road2.setPosition(width/2.5, road1.getPosition().y - roadTexture.getSize().y);
}

int roadLanes[2] = {404,540}; // road lanes for NPC cars

// specialized function loaded only once in main
int loadNPC1(int n){
    if (!NPC1CarTexture.loadFromFile(*conf::colors[n])) {
        std::cerr << "Failed to load NPC1 texture\n";
        return -1;
    }
    if (
        loadNPC(NPC1Car,NPC1CarTexture, getRandomNumber(gameClock,0,47),NPC1carPos.x,NPC1carPos.y) == -1) // reload the NPC car if it goes off screen
    {
        return -1;
    } else {
        return 0;
    }
    
}

// specialized function loaded only once in main
int loadNPC2(int n){
    if (!NPC2CarTexture.loadFromFile(*conf::colors[n])) {
        std::cerr << "Failed to load NPC2 texture\n";
        return -1;
    }
    if (loadNPC(NPC2Car,NPC2CarTexture, getRandomNumber(gameClock,0,47),NPC2carPos.x,NPC2carPos.y) == -1) // reload the NPC car if it goes off screen
    {return -1;}
    else
    {return 0;}
    
}

void moveNPCs(float scrollSpeed1,float scrollSpeed2, float deltaTime){
    int rand1 = 0,rand2 = 0;
    
    NPC1Car.move(0, scrollSpeed1 * deltaTime);
    NPC2Car.move(0, scrollSpeed2 * deltaTime);

    if (NPC1Car.getPosition().y > height + 30){
        rand1 = getRandomNumber(gameClock, roadLanes[0], roadLanes[1]);
        NPC1carPos.x = rand1;                                                 // update the NPC car position
        NPC1carPos.y -= static_cast<int>(getRandomNumber(gameClock, 0, 500)); // update the NPC car position
        loadNPC(NPC1Car, NPC1CarTexture, getRandomNumber(gameClock, 0, 47), NPC1carPos.x, NPC1carPos.y); // reload the NPC car if it goes off screen
    }

    if (NPC2Car.getPosition().y > height + 30){
        rand2 = getRandomNumber(gameClock, roadLanes[0], roadLanes[1]) + 50;
        NPC2carPos.x = rand2;                                                  // update the NPC car position
        NPC2carPos.y -= static_cast<int>(getRandomNumber(gameClock, 0, 1000)); // update the NPC car position
        loadNPC(NPC2Car, NPC2CarTexture, getRandomNumber(gameClock, 0, 47), NPC2carPos.x, NPC2carPos.y); // reload the NPC car if it goes off screen
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


bool collision(sf::Sprite s1, sf::Sprite s2) {
    return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}

// all collisions
bool playerCollision(){
    if (collision(playerCar, NPC1Car)) {
        return true; // Collision occurred
    }
    if (collision(playerCar, NPC2Car)) {
        return true; // Collision occurred
    }
    return false; // No collision
}

// defines all movements done by the player car, whether they are controlled by player or the environment
void movePlayer(float dT, float speedVert, float speedHorz){
    int bounds = playerBounds();

    // player will down with the NPC car if they collide
    if (collision(playerCar, NPC1Car))
    {
        playerCar.moveDown(dT, conf::NPC1CarSpeed); // move down WITH the NPC1 Car if collision occurs
    }
    // player will down with the NPC car if they collide
    if (collision(playerCar, NPC2Car))
    {
        playerCar.moveDown(dT, conf::NPC2CarSpeed); // move down WITH the NPC2 Car if collision occurs
    }
    

    // Left movement (only if the player is not at the left boundary)
    if (pressedLeft()   && bounds != 1 && bounds != 4 && bounds != 7)
        playerCar.moveLeft(dT, speedHorz);

    // Right movement (only if the player is not at the right boundary)
    if (pressedRight()  && bounds != 3 && bounds != 6 && bounds != 9)
        playerCar.moveRight(dT, speedHorz);

    // Up movement (only if the player is not at the top boundary)
    if (pressedUp()     && bounds != 1 && bounds != 2 && bounds != 3 && !collision(playerCar, NPC2Car) && !collision(playerCar, NPC1Car))
        playerCar.moveUp(dT, speedVert);

    // Down movement (only if the player is not at the bottom boundary)
    if (pressedDown()   && bounds != 7 && bounds != 8 && bounds != 9)
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
    // Clear the console screen
        // system("cls"); // Use "clear" instead of "cls" if on Linux/MacOS
        cursorUp(17);

        // Print information in a readable format
        for (size_t i = 0; i < 51; i++)
        {
            cout << "=";
        }
        cout<<endl;
        cout /* << left << setw(30) */ << "Screen res:           " /* << right */ << width << ", " << height << endl;
        cout /* << left << setw(30) */ << "FPS:                  " /* << right */ << 1.f / clock.restart().asSeconds() << endl;
        cout /* << left << setw(30) */ << "Player Car Position:  " /* << right */ << playerCar.getPosition().x << ", " << playerCar.getPosition().y << endl;
        cout /* << left << setw(30) */ << "NPC1 Car Position:    " /* << right */ << NPC1Car.getPosition().x << ", " << NPC1Car.getPosition().y << endl;
        cout /* << left << setw(30) */ << "NPC2 Car Position:    " /* << right */ << NPC2Car.getPosition().x << ", " << NPC2Car.getPosition().y << endl;
        cout /* << left << setw(30) */ << "Road1 Position:       " /* << right */ << road1.getPosition().x << ", " << road1.getPosition().y << endl;
        cout /* << left << setw(30) */ << "Road2 Position:       " /* << right */ << road2.getPosition().x << ", " << road2.getPosition().y << endl;
        cout /* << left << setw(30) */ << "Player Car Scale:     " /* << right */ << playerCar.getScale().x << ", " << playerCar.getScale().y << endl;
        cout /* << left << setw(30) */ << "Player speed:         " /* << right */ << playerCar.speed << endl;
        cout /* << left << setw(30) */ << "Road dimensions:      " /* << right */ << roadTexture.getSize().x << ", " << roadTexture.getSize().y << endl;
        cout /* << left << setw(30) */ << "Bound:                " /* << right */ << playerBounds() << endl;
        cout /* << left << setw(30) */ << "Collision npc1:       " /* << right */ << collision(playerCar,NPC1Car) << endl;
        cout /* << left << setw(30) */ << "Collision npc2:       " /* << right */ << collision(playerCar,NPC2Car) << endl;
        cout /* << left << setw(30) */ << "Car W x H:            " /* << right */ << playerCar.getGlobalBounds().width << ", " << playerCar.getGlobalBounds().height << endl;
        cout /* << left << setw(30) */ << "rand, rl1, rl2, size: " /* << right */ << getRandomNumber(gameClock, roadLanes[0], roadLanes[1]) << ", " << roadLanes[0] << ", " << roadLanes[1] << ", " << roadTexture.getSize().x << endl;
        
        for (size_t i = 0; i < 51; i++)
        {
            cout << "=";
        }
        cout<<endl;
}

void gameStep(float dT){
    conf::NPC1ScrollSpeed = conf::playerCarSpeed - conf::NPC1CarSpeed; // should this be redefined in main ?
    conf::NPC2ScrollSpeed = conf::playerCarSpeed - conf::NPC2CarSpeed; // should this be redefined in main ?

        // increasing acceleration on press up
        if (pressedUp()) {
            conf::playerCarAcceleration += 20; // increase the acceleration of the road 
        } else if (pressedDown() && conf::playerCarSpeed > 0) {
            conf::playerCarAcceleration -= 20; // decrease the acceleration of the road 
        } else

        

        // only speed up until top speed is reached
        if (playerCar.topSpeed > conf::playerCarSpeed) {
            conf::playerCarSpeed += conf::playerCarAcceleration * dT; // increase the speed of the road 
        } 

        //? Scroll road background
        moveBackground(conf::playerCarSpeed,dT);
        

        //? Scroll NPCs background
        moveNPCs(conf::NPC1ScrollSpeed,conf::NPC2ScrollSpeed, dT);


        //? Player car movement (basic)
        movePlayer(dT, 250,250); // this is the speed with which the player car ACROSS moves
}

void renderElements(
    elements::background b1,
    elements::background b2, 
    elements::PlayerCar p,
    elements::PlayerCar p1,
    elements::PlayerCar p2
){
    // order of render determines the position of the elements
    window.clear(conf::darkGreen);
    window.draw(b1);
    window.draw(b2);
    window.draw(p);
    window.draw(p1);
    window.draw(p2);

   /*  // window size test
    // Create a transparent black rectangle
    sf::RectangleShape overlay(sf::Vector2f(width, height));
    overlay.setFillColor(sf::Color(0, 0, 0, 128)); // RGBA: Black with 50% transparency
    window.draw(overlay); // Draw the rectangle over the screen */



    window.display();
}



int main() {
    hideCursor();
    // std::srand(static_cast<unsigned int>(std::time(nullptr))); // creating rand seed
    float roadScrollSpeed = conf::roadScrollSpeed;
    if (
        // order of loading determines the order of rendering
        loadNPC1(0) == -1
        ||loadNPC2(3) == -1
        ||loadPlayer() == -1
        ||loadStructures() == -1
    ) {
        std::cerr << "Failed to load \n";
        return -1;
    }
    

    // float roadScrollSpeed = conf::roadScrollSpeed;
    

    int i = 1000;
    // Main game loop
    while (window.isOpen()) {
        if(i==0)
        {
            debugInfo(gameClock);
            i = 1000;
        }
        i--;
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // close program by pressing ESC
        if (pressedESC()) {
            window.close();
        }
        float deltaTime = gameClock.restart().asSeconds();

        gameStep(deltaTime);

        //? final rendering of all elements to screen
        renderElements(road1,road2,playerCar,NPC1Car,NPC2Car);
    }
    
    // delete conf::colors[48];

    return 0;
}
