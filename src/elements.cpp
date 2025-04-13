#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "elements.hpp"

#include <iostream>
using namespace std;

namespace elements
{

// Car constructor
Car::Car(std::string color, std::string model, int topSpeed) {
    this->color = color;
    this->model = model;
    this->topSpeed = topSpeed;
}

// Truck constructors
truck::truck() : Car() {
    size = 10;
}

truck::truck(std::string color, std::string model, int topSpeed, int size)
    : Car(color, model, topSpeed) {
    this->size = size;
}

// NPCCar static member init
int NPCCar::topSpeed = 200;

// NPCCar constructor
NPCCar::NPCCar() {
    topSpeed = 200;
}

// PlayerCar constructor
PlayerCar::PlayerCar(const sf::Texture& texture) : sf::Sprite(texture) {
    setPosition(100, 100);
}

// Movement methods
void PlayerCar::moveLeft(float deltaTime) {
    this->sf::Sprite::move(-300 * deltaTime, 0);
}

void PlayerCar::moveRight(float deltaTime) {
    this->sf::Sprite::move(300 * deltaTime, 0);
}

void PlayerCar::moveUp(float deltaTime) {
    this->sf::Sprite::move(0, -300 * deltaTime);
}

void PlayerCar::moveDown(float deltaTime) {
    this->sf::Sprite::move(0, 300 * deltaTime);
}

// Background constructor
background::background(const sf::Texture& texture) : sf::Sprite(texture) {
    setPosition(0, 0);
}




} // namespace elements