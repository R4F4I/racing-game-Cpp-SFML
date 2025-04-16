#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "elements.hpp"

#include <iostream>
using namespace std;

namespace elements
{

// Car constructor
Car::Car(std::string color, std::string model, float topSpeed, float speed) {
    this->color = color;
    this->model = model;
    this->topSpeed = topSpeed;
    this->speed = speed;
}

// Truck constructors
truck::truck() : Car() {
    size = 10;
}

truck::truck(std::string color, std::string model, float topSpeed, int size)
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
PlayerCar::PlayerCar(){
    setPosition(100, 100);
}
PlayerCar::PlayerCar(const sf::Texture& texture) : sf::Sprite(texture) {
    setPosition(100, 100);
}

// Movement methods
void PlayerCar::moveLeft(float deltaTime,float speed) {
    this->sf::Sprite::move(-speed * deltaTime, 0);
}

void PlayerCar::moveRight(float deltaTime,float speed) {
    this->sf::Sprite::move(speed * deltaTime, 0);
}

void PlayerCar::moveUp(float deltaTime,float speed) {
    this->sf::Sprite::move(0, -speed * deltaTime);
}

void PlayerCar::moveDown(float deltaTime,float speed) {
    this->sf::Sprite::move(0, speed * deltaTime);
}

// Background constructor
background::background() {
    setPosition(0, 0);
}
background::background(const sf::Texture& texture) : sf::Sprite(texture) {
    setPosition(0, 0);
}




} // namespace elements