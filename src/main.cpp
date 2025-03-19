#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include "events.hpp"
#include "configuration.hpp"
#include "stars.hpp"


std::vector<Star> createStars(uint32_t count) {
    std::vector<Star> stars;
    stars.reserve(count);

    // random num generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    // create randomly distributed stars on screen
    for (uint32_t i{ count };i--;) {
        float const x = dis(gen) * conf::window_size_f.x;
        float const y = dis(gen) * conf::window_size_f.y;


        stars.push_back({{x,y}});
    }

    return stars;
}


int main() {

    auto window = sf::RenderWindow({conf::window_size.x,conf::window_size.y}, "SFML works!");
    window.setFramerateLimit(conf::max_framerate);

    // sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    std::vector<Star> stars = createStars(conf::count);


    while (window.isOpen()) {
        
        processEvents(window);

        // renderering occurs here 
        window.clear();
        window.display();

    }

    return 0;
}