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
sf::RenderWindow window(sf::VideoMode(width, height), conf::windowTitle);

///////////////////////////////////////////////////
//? declare road texture
sf::Texture roadTexture;


///////////////////////////////////////////////////
//? declare car texture
sf::Texture playerCarTexture;

///////////////////////////////////////////////////

///////////////////////////////////////////////////
//? declare road1 and road2 // constructor only called in loadStructures()
elements::background road1;
elements::background road2;
///////////////////////////////////////////////////
//? declare playerCar // constructor only called in loadPlayer()
elements::PlayerCar playerCar;
///////////////////////////////////////////////////


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

    if (!playerCarTexture.loadFromFile(conf::orangeCar)) {
        std::cerr << "Failed to load player texture\n";
        return -1;
    }

    playerCar = elements::PlayerCar(playerCarTexture);

    playerCar.setScale(conf::CarsScale, conf::CarsScale); // Scale if needed
    playerCar.setPosition(PcarPos.x, PcarPos.y); // Center near bottom
}



void debugInfo(sf::Clock clock){
    // Clear the console screen
        system("cls"); // Use "clear" instead of "cls" if on Linux/MacOS

        // Print information in a readable format
        cout << "=============================" << endl;
        cout << "FPS: " << 1.f / clock.restart().asSeconds() << endl;
        cout << "Player Car Position: " << playerCar.getPosition().x << ", " << playerCar.getPosition().y << endl;
        cout << "Road1 Position: " << road1.getPosition().x << ", " << road1.getPosition().y << endl;
        cout << "Road2 Position: " << road2.getPosition().x << ", " << road2.getPosition().y << endl;
        cout << "Player Car Scale: " << playerCar.getScale().x << ", " << playerCar.getScale().y << endl;
        cout << "Road1 Scale: " << road1.getScale().x << ", " << road1.getScale().y << endl;
        cout << "=============================" << endl;
}

void moveBackground(float scrollSpeed,float deltaTime){
    road1.move(0, scrollSpeed * deltaTime);
    road2.move(0, scrollSpeed * deltaTime);

    if (road1.getPosition().y >= roadTexture.getSize().y)
        road1.setPosition(width/2.5, road2.getPosition().y - roadTexture.getSize().y);
    if (road2.getPosition().y >= roadTexture.getSize().y)
        road2.setPosition(width/2.5, road1.getPosition().y - roadTexture.getSize().y);
}


// todo: function that checks if player car is out of bounds
// the function returns 
//  1 if the player is above    the screen //y<0
//  2 if the player is below    the screen //y>height
//  3 if the player is left of  the screen //x<0
//  4 if the player is right of the screen //x>width
int playerBounds() {
    // Top boundary
    if (playerCar.getPosition().y < 0) {
        return 1;
    }
    // Bottom boundary (account for car height)
    if (playerCar.getPosition().y /* + playerCar.getGlobalBounds().height */ > height-20) {
        return 2;
    }
    // Left boundary
    if (playerCar.getPosition().x < 0) {
        return 3;
    }
    // Right boundary (account for car width)
    if (playerCar.getPosition().x /* + playerCar.getGlobalBounds().width */ > width-20) {
        return 4;
    }
    // No boundary reached
    return 0;
}

void updatePlayerPosition(float deltaTime){
    int bounds = playerBounds();


    // Left movement (only if the player is not at the left boundary)
    if (pressedLeft() && bounds != 3)
        playerCar.moveLeft(deltaTime);

    // Right movement (only if the player is not at the right boundary)
    if (pressedRight() && bounds != 4)
        playerCar.moveRight(deltaTime);

    // Up movement (only if the player is not at the top boundary)
    if (pressedUp() && bounds != 1)
        playerCar.moveUp(deltaTime);

    // Down movement (only if the player is not at the bottom boundary)
    if (pressedDown() && bounds != 2)
        playerCar.moveDown(deltaTime);
}

void renderElements(elements::background b1,elements::background b2, elements::PlayerCar p){
    window.clear(conf::bgColor);
    window.draw(b1);
    window.draw(b2);
    window.draw(p);

   /*  // window size test
    // Create a transparent black rectangle
    sf::RectangleShape overlay(sf::Vector2f(width, height));
    overlay.setFillColor(sf::Color(0, 0, 0, 128)); // RGBA: Black with 50% transparency
    window.draw(overlay); // Draw the rectangle over the screen */



    window.display();
}



int main() {

    

    if (
        loadPlayer() == -1||
        loadStructures() == -1
    ) {
        std::cerr << "Failed to load \n";
        return -1;
    }
    

    float scrollSpeed = conf::scrollSpeed;
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
        moveBackground(scrollSpeed,deltaTime);

        //? Player car movement (basic)
        updatePlayerPosition(deltaTime);

        //? final rendering of all elements to screen
        renderElements(road1,road2,playerCar);
    }
    return 0;
}
