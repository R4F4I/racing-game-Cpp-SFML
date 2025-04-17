#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cstdlib>         // For std::rand and std::srand
#include <ctime>          // For std::time
#include <iostream>
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
struct conf::NPCCarPosition NPCcarPos;
sf::RenderWindow window(sf::VideoMode(width, height), conf::windowTitle);

///////////////////////////////////////////////////
//? declare road texture
sf::Texture roadTexture;


///////////////////////////////////////////////////
//? declare car texture
sf::Texture playerCarTexture;
sf::Texture NPCCarTexture;

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
///////////////////////////////////////////////////

///////////////////////////////////////////////////

// rand gen
int getRandomNumber(sf::Clock& clock, int min = 0, int max = 47) {
    // Use the elapsed time from the clock as a seed
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generate a random number between 0 and 47
    return min + std::rand() % (max - min + 1);
}

float getRandomNumber(sf::Clock& clock, float min, float max) {
    // Use the elapsed time from the clock as a seed
    // std::srand(RAND_MAX);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    // Generate a random float between min and max
    float random = static_cast<float>(std::rand()+10) / static_cast<float>(RAND_MAX); // Random value between 0 and 1
    return min + random * (max - min); // Scale to the range [min, max]
}

//assign speeds
void valueSetter(){
    // Set the speed of the player car and NPC car
    playerCar.speed = conf::playerCarSpeed;
    NPC1Car.speed = conf::NPCCarSpeed;
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

int loadNPCs(int carColorIndex){
    if (!NPCCarTexture.loadFromFile(*conf::colors[carColorIndex])) {
        std::cerr << "Failed to load NPC1 texture\n";
        return -1;
    }
    
    NPC1Car = elements::PlayerCar(NPCCarTexture);
    
    NPC1Car.setScale(conf::CarsScale, conf::CarsScale); // Scale if needed
    NPC1Car.setPosition(NPCcarPos.x, NPCcarPos.y); // Center near bottom
}

void moveBackground(float scrollSpeed,float deltaTime){
    road1.move(0, scrollSpeed * deltaTime);
    road2.move(0, scrollSpeed * deltaTime);
    
    // width-roadTexture.getSize().x explanation:
    // for (width of the screen - width of the road) give us an offset
    // when centering, if we directly used width/2 the road position the road will look 'off' because the road's position is set from left side, (width- getsize.x)/2 gives us a better result, however (width- getsize.x) is too long and complex to follow
    if (road1.getPosition().y >= roadTexture.getSize().y)
    road1.setPosition((width-roadTexture.getSize().x)/2, road2.getPosition().y - roadTexture.getSize().y);
    // road1.setPosition(width/2.5, road2.getPosition().y - roadTexture.getSize().y);
    if (road2.getPosition().y >= roadTexture.getSize().y)
    road2.setPosition((width-roadTexture.getSize().x)/2, road1.getPosition().y - roadTexture.getSize().y);
    // road2.setPosition(width/2.5, road1.getPosition().y - roadTexture.getSize().y);
}

int roadLanes[2] = {398,547}; // road lanes for NPC cars

void moveNPCs(float scrollSpeed,float deltaTime){
    NPC1Car.move(0, scrollSpeed * deltaTime);

    if (NPC1Car.getPosition().y > height+30){
        loadNPCs(getRandomNumber(gameClock,0,47)); // reload the NPC car if it goes off screen
        NPC1Car.setPosition(getRandomNumber(gameClock,roadLanes[0],roadLanes[1]), NPCcarPos.y); // Center near bottom
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
    return false; // No collision
}


void movePlayer(float deltaTime, float speedVert, float speedHorz){
    int bounds = playerBounds();

    // player will down with the NPC car if they collide
    if (collision(playerCar, NPC1Car))
    {
        playerCar.moveDown(deltaTime, conf::NPCCarSpeed); // move down if collision occurs
    }
    

    // Left movement (only if the player is not at the left boundary)
    if (pressedLeft()   && bounds != 1 && bounds != 4 && bounds != 7)
        playerCar.moveLeft(deltaTime, speedHorz);

    // Right movement (only if the player is not at the right boundary)
    if (pressedRight()  && bounds != 3 && bounds != 6 && bounds != 9)
        playerCar.moveRight(deltaTime, speedHorz);

    // Up movement (only if the player is not at the top boundary)
    if (pressedUp()     && bounds != 1 && bounds != 2 && bounds != 3 && !collision(playerCar, NPC1Car))
        playerCar.moveUp(deltaTime, speedVert);

    // Down movement (only if the player is not at the bottom boundary)
    if (pressedDown()   && bounds != 7 && bounds != 8 && bounds != 9)
        playerCar.moveDown(deltaTime, speedVert);
}


void debugInfo(sf::Clock clock){
    // Clear the console screen
        system("cls"); // Use "clear" instead of "cls" if on Linux/MacOS

        // Print information in a readable format
        cout << "=============================" << endl;
        cout << "screen res: " << width << ", " << height << endl;
        cout << "FPS: " << 1.f / clock.restart().asSeconds() << endl;
        cout << "Player Car Position: " << playerCar.getPosition().x << ", " << playerCar.getPosition().y << endl;
        cout << "NPC Car Position: " << NPC1Car.getPosition().x << ", " << NPC1Car.getPosition().y << endl;
        cout << "Road1 Position: " << road1.getPosition().x << ", " << road1.getPosition().y << endl;
        cout << "Road2 Position: " << road2.getPosition().x << ", " << road2.getPosition().y << endl;
        cout << "Player Car Scale: " << playerCar.getScale().x << ", " << playerCar.getScale().y << endl;
        cout << "Road dimensions: " << roadTexture.getSize().x << ", " << roadTexture.getSize().y << endl;
        cout << "Bound: " << playerBounds() << endl;
        cout << "Collision: " << collision(playerCar, NPC1Car) << endl;
        cout << "Player Car Width, Height: " << playerCar.getGlobalBounds().width <<", "<<playerCar.getGlobalBounds().height<< endl;
        cout << "rand num, rl1 , rl2,size: " << getRandomNumber(gameClock,roadLanes[0],roadLanes[1]) <<", "<<roadLanes[0]<<", "<< roadLanes[1]<<", "<<roadTexture.getSize().x << endl;
        cout << "=============================" << endl;
}

void renderElements(
    elements::background b1,
    elements::background b2, 
    elements::PlayerCar p1,
    elements::PlayerCar p2
){
    // order of render determines the position of the elements
    window.clear(conf::darkGreen);
    window.draw(b1);
    window.draw(b2);
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
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // creating rand seed
    float roadScrollSpeed = conf::roadScrollSpeed;
    if (
        // order of loading determines the order of rendering
        loadNPCs(0) == -1
        ||loadPlayer() == -1
        ||loadStructures() == -1
    ) {
        std::cerr << "Failed to load \n";
        return -1;
    }
    

    // float roadScrollSpeed = conf::roadScrollSpeed;
    

    // Main game loop
    while (window.isOpen()) {
        
        debugInfo(gameClock);
        
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

        conf::NPCScrollSpeed = conf::playerCarSpeed - conf::NPCCarSpeed; // should this be redefined in main ?

        // increasing acceleration on press up
        if (pressedUp()) {
            conf::playerCarAcceleration += 20; // increase the acceleration of the road 
        } else if (pressedDown()) {
            conf::playerCarAcceleration -= 20; // decrease the acceleration of the road 
        } else

        

        // only speed up until top speed is reached
        if (playerCar.topSpeed > conf::playerCarSpeed) {
            conf::playerCarSpeed += conf::playerCarAcceleration * deltaTime; // increase the speed of the road 
        } 

        //? Scroll road background
        moveBackground(conf::playerCarSpeed,deltaTime);
        

        //? Scroll NPCs background
        moveNPCs(conf::NPCScrollSpeed,deltaTime);


        //? Player car movement (basic)
        movePlayer(deltaTime, 300,250); // this is the speed with which the player car ACROSS moves

        //? final rendering of all elements to screen
        renderElements(road1,road2,playerCar,NPC1Car);
    }
    
    // delete conf::colors[48];

    return 0;
}
