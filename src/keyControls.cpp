#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

namespace key{
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
    bool pressedW(){
        return sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    }
    bool pressedA(){
        return sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    }
    bool pressedS(){
        return sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    }
    bool pressedD(){
        return sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    }
}