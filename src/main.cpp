#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "elements.hpp"
#include "keyControls.hpp"
#include "configuration.hpp"

using namespace std;

//  DECLARATIONS
//-----------------------------------------------//

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

    road1.setPosition(width/2.5, 0);
    road2.setPosition(width/2.5, -roadTexture.getSize().y);

}

int loadPlayer(){

    if (!playerCarTexture.loadFromFile(conf::blueCar)) {
        std::cerr << "Failed to load player texture\n";
        return -1;
    }

    playerCar = elements::PlayerCar(playerCarTexture);

    playerCar.setScale(conf::CarsScale, conf::CarsScale); // Scale if needed
    playerCar.setPosition(PcarPos.x, PcarPos.y); // Center near bottom
}

int loadNPCs(){
    if (!NPCCarTexture.loadFromFile(conf::whiteCar)) {
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

    if (road1.getPosition().y >= roadTexture.getSize().y)
        road1.setPosition(width/2.5, road2.getPosition().y - roadTexture.getSize().y);
    if (road2.getPosition().y >= roadTexture.getSize().y)
        road2.setPosition(width/2.5, road1.getPosition().y - roadTexture.getSize().y);
}
void moveNPCs(float scrollSpeed,float deltaTime){
    NPC1Car.move(0, scrollSpeed * deltaTime);

    if (NPC1Car.getPosition().y > height+30)
        NPC1Car.setPosition(NPCcarPos.x, NPCcarPos.y);
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
int playerBounds() {

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
    
     // Check if the bounding boxes of the two sprites intersect
     // todo: this collision works for road craters
     // for cars the player must not be able to move inside the car
    return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
    /*
    // collision of player only from front
    float a1[2] = {s1.getPosition().x                               , s1.getPosition().y};
    float a2[2] = {s1.getPosition().x + s1.getGlobalBounds().width  , s1.getPosition().y};
    float a3[2] = {s1.getPosition().x                               , s1.getPosition().y + s1.getGlobalBounds().height};
    float a4[2] = {s1.getPosition().x + s1.getGlobalBounds().width  , s1.getPosition().y + s1.getGlobalBounds().height};
    
    float b1[2] = {s2.getPosition().x                               , s2.getPosition().y};
    float b2[2] = {s2.getPosition().x + s2.getGlobalBounds().width  , s2.getPosition().y};
    float b3[2] = {s2.getPosition().x                               , s2.getPosition().y + s2.getGlobalBounds().height};
    float b4[2] = {s2.getPosition().x + s2.getGlobalBounds().width  , s2.getPosition().y + s2.getGlobalBounds().height};
    

    if (a1<b2 ||a1<b4 || a2<b1 || a2<b3) {
        // Collision detected
        return true;
    } else {
        // No collision
        return false;
    } */
}

// all collisions
bool playerCollision(){
    if (collision(playerCar, NPC1Car)) {
        // Handle collision (e.g., reset player position, reduce health, etc.)
        // std::cout << "Collision detected!" << std::endl;
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
        cout << "Road1 Scale: " << road1.getScale().x << ", " << road1.getScale().y << endl;
        cout << "Bound: " << playerBounds() << endl;
        cout << "Collision: " << collision(playerCar, NPC1Car) << endl;
        cout << "Player Car Width, Height: " << playerCar.getGlobalBounds().width <<", "<<playerCar.getGlobalBounds().height<< endl;
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
    if (
        // order of loading determines the order of rendering
        loadNPCs() == -1
        ||loadPlayer() == -1
        ||loadStructures() == -1
    ) {
        std::cerr << "Failed to load \n";
        return -1;
    }
    

    // float roadScrollSpeed = conf::roadScrollSpeed;
    sf::Clock clock;

    // Main game loop
    while (window.isOpen()) {
        
        debugInfo(clock);
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // close program by pressing ESC
        if (pressedESC()) {
            window.close();
        }
        float deltaTime = clock.restart().asSeconds();

        //? Scroll road background
        moveBackground(conf::roadScrollSpeed,deltaTime);
        

        //? Scroll NPCs background
        moveNPCs(conf::NPCScrollSpeed,deltaTime);


        //? Player car movement (basic)
        movePlayer(deltaTime, 300,250); // this is the speed with which the player car ACROSS moves

        //? final rendering of all elements to screen
        renderElements(road1,road2,playerCar,NPC1Car);
    }
    return 0;
}
