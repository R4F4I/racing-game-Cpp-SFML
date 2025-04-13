#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

using namespace std;

namespace elements
{
class Car : public virtual sf::Sprite
{
private:
    string color,model;
    int topSpeed;
public:
    /* Car(){
        color = "Red";
        model = "Toyota";
        topSpeed = 200;
    } */

    Car(string color = "Red",string model = "Toyota",int topSpeed = 200){
        this->color = color;
        this->model = model;
        this->topSpeed = topSpeed;
    }


};

class truck : public Car
{
private:
    int size;
public:
    truck():Car(){
        size = 10;
    }
    truck(string color,string model,int topSpeed,int size):Car(color,model,topSpeed){
        this->size = size;
    }
};

class NPCCar : public Car
{
private:
    static int topSpeed;
public:
    NPCCar(/* args */){
        topSpeed = 200;
    }
    
};

int NPCCar::topSpeed = 200;

class PlayerCar : public Car
{
private:
    /* data */
public:
    PlayerCar(const sf::Texture& texture) : sf::Sprite(texture) {
        // maybe set initial position or scale here
        setPosition(100, 100);
    }

    void moveLeft(float deltaTime) {
        this->sf::Sprite::move(-300 * deltaTime, 0);
    }
    void moveRight(float deltaTime) {
        this->sf::Sprite::move(300 * deltaTime, 0);
    }
    void moveUp(float deltaTime) {
        this->sf::Sprite::move(0,-300 * deltaTime);
    }
    void moveDown(float deltaTime) {
        this->sf::Sprite::move(0,300 * deltaTime);
    }


};

class background : public sf::Sprite
{
private:
    /* data */

public:
    background(const sf::Texture& texture) : sf::Sprite(texture) {
        // maybe set initial position or scale here
        setPosition(0, 0);
    }


};

    
} // namespace elements

bool pressedESC(){
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
}
bool pressedLeft(){
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
}
bool pressedRight(){
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
}
bool pressedUp(){
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
}
bool pressedDown(){
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
}

int main() {
    float width = 800;
    float height = 600;
    sf::RenderWindow window(sf::VideoMode(width, height), "Racing Game with Textures");

    // Load road texture
    sf::Texture roadTexture;
    if (!roadTexture.loadFromFile("res/road.png")) {
        std::cerr << "Failed to load road.png\n";
        return -1;
    }

    // Two road sprites for scrolling effect
    elements::background road1(roadTexture);
    elements::background road2(roadTexture);
    road1.setPosition(width/2.5, 0);
    road2.setPosition(width/2.5, -roadTexture.getSize().y);

    float scrollSpeed = 200.f;

    // Load car texture
    sf::Texture playerCarTexture;
    if (!playerCarTexture.loadFromFile("res/BlueCar.png")) {
        std::cerr << "Failed to load BlueCar.png\n";
        return -1;
    }

    // Main player's car
    elements::PlayerCar playerCar(playerCarTexture);
    playerCar.setScale(0.2f, 0.2f); // Scale if needed
    playerCar.setPosition(375, 450); // Center near bottom

    sf::Clock clock;

    // Main game loop
    while (window.isOpen()) {
        /* // Clear the console screen
        system("cls"); // Use "clear" instead of "cls" if on Linux/MacOS

        // Print information in a readable format
        cout << "=============================" << endl;
        cout << "FPS: " << 1.f / clock.restart().asSeconds() << endl;
        cout << "Player Car Position: " << playerCar.getPosition().x << ", " << playerCar.getPosition().y << endl;
        cout << "Road1 Position: " << road1.getPosition().x << ", " << road1.getPosition().y << endl;
        cout << "Road2 Position: " << road2.getPosition().x << ", " << road2.getPosition().y << endl;
        cout << "Player Car Scale: " << playerCar.getScale().x << ", " << playerCar.getScale().y << endl;
        cout << "Road1 Scale: " << road1.getScale().x << ", " << road1.getScale().y << endl;
        cout << "=============================" << endl; */
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
        road1.move(0, scrollSpeed * deltaTime);
        road2.move(0, scrollSpeed * deltaTime);

        if (road1.getPosition().y >= roadTexture.getSize().y)
            road1.setPosition(width/2.5, road2.getPosition().y - roadTexture.getSize().y);
        if (road2.getPosition().y >= roadTexture.getSize().y)
            road2.setPosition(width/2.5, road1.getPosition().y - roadTexture.getSize().y);

        // // Player car movement (basic)
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

        window.clear();
        window.draw(road1);
        window.draw(road2);
        window.draw(playerCar);
        window.display();
    }

    return 0;
}
