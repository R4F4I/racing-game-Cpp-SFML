#ifndef ELEMENTARY_SFML_ELEMENTS_HPP
#define ELEMENTARY_SFML_ELEMENTS_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace elements {

class Car : public virtual sf::Sprite {
private:
    std::string color, model;
    int topSpeed;

public:
    Car(std::string color = "Red", std::string model = "Toyota", int topSpeed = 200);
};

class truck : public Car {
private:
    int size;

public:
    truck();
    truck(std::string color, std::string model, int topSpeed, int size);
};

class NPCCar : public Car {
private:
    static int topSpeed;

public:
    NPCCar();
};

class PlayerCar : public Car {
public:
    PlayerCar(const sf::Texture& texture);

    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);
    void moveUp(float deltaTime);
    void moveDown(float deltaTime);
};

class background : public sf::Sprite {
public:
    background(const sf::Texture& texture);
};

} // namespace elements

#endif // ELEMENTARY_SFML_ELEMENTS_HPP
