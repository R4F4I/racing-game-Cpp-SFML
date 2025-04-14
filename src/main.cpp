#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "elements.hpp"
#include "keyControls.hpp"
#include "configuration.hpp"

using namespace std;

float width = conf::width;
float height = conf::height;
struct conf::playerCarPosition PcarPos;
sf::RenderWindow window(sf::VideoMode(width, height), "Racing Game with Textures");
sf::Texture roadTexture;

void loadStructures(){
    // Load road texture
    if (!roadTexture.loadFromFile(conf::road)) {
        std::cerr << "Failed to load road.png\n";
        return -1;
    }

    // Two road sprites for scrolling effect
    elements::background road1(roadTexture);
    elements::background road2(roadTexture);
    road1.setPosition(width/2.5, 0);
    road2.setPosition(width/2.5, -roadTexture.getSize().y);

    

}

void loadPlayer(){

    // Load car texture
    sf::Texture playerCarTexture;
    if (!playerCarTexture.loadFromFile(conf::blueCar)) {
        std::cerr << "Failed to load BlueCar.png\n";
        return -1;
    }

    // Main player's car
    elements::PlayerCar playerCar(playerCarTexture);
    playerCar.setScale(conf::CarsScale, conf::CarsScale); // Scale if needed
    playerCar.setPosition(PcarPos.x, PcarPos.y); // Center near bottom
}

void debugInfo(){
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

void updatePlayerPosition(float deltaTime){
    // left
    if (pressedLeft())
        playerCar.moveLeft(deltaTime);
    // right
    if (pressedRight())
        playerCar.moveRight(deltaTime);
    // up
    if (pressedUp())
        playerCar.moveUp(deltaTime);
    // down
    if (pressedDown())
        playerCar.moveDown(deltaTime);

}

void renderElements(elements::background b1,elements::background b2, elements::PlayerCar p){
    window.clear();
    window.draw(b1);
    window.draw(b2);
    window.draw(p);
    window.display();
}

int main() {

    loadStructures();
    loadPlayer();

    float scrollSpeed = conf::scrollSpeed;
    sf::Clock clock;

    // Main game loop
    while (window.isOpen()) {
        // debugInfo();
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

        // Scroll road background
        moveBackground(scrollSpeed,deltaTime);

        //? Player car movement (basic)
        updatePlayerPosition(deltaTime);

        // final rendering of all elements to screen
        renderElements(road1,road2,playerCar);
        
    }

    return 0;
}
