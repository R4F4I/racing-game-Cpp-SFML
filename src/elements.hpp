#ifndef ELEMENTARY_SFML_ELEMENTS_HPP
#define ELEMENTARY_SFML_ELEMENTS_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace elements {

class Car : public virtual sf::Sprite {
private:
    std::string color, model;

public:
    float topSpeed;
    float speed;
    friend void valueSetter();
    Car(std::string color = "Red", std::string model = "Toyota", float topSpeed = 500.f, float speed = 0.f);
};

class truck : public Car {
private:
    int size;

public:
    truck();
    truck(std::string color, std::string model, float topSpeed, int size);
};

class NPCCar : public Car {
private:
    static int topSpeed;

public:
    NPCCar();
};

class PlayerCar : public Car {
public:
    PlayerCar();
    PlayerCar(const sf::Texture& texture);

    void moveLeft(float deltaTime, float speed);
    void moveRight(float deltaTime, float speed);
    void moveUp(float deltaTime, float speed);
    void moveDown(float deltaTime, float speed);
};

class background : public sf::Sprite {
public:
    background();
    background(const sf::Texture& texture);
};

} // namespace elements

#endif // ELEMENTARY_SFML_ELEMENTS_HPP
