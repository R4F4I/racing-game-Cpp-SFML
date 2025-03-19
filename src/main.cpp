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
        // added 0.5 center all the values, because the starting values in the window start from top right
        float const x = (dis(gen) - 0.5f) * conf::window_size_f.x;
        float const y = (dis(gen) - 0.5f) * conf::window_size_f.y;

        // random depth z for each star
        float const z = dis(gen) * (conf::far - conf::near)+conf::near;


        stars.push_back({{x,y},z});
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

        sf::CircleShape shape{ conf::radius };
        shape.setOrigin(conf::radius, conf::radius);

        for (auto const & s: stars)
        {
            // inverse because more depth, lesser the scale
            float const scale = 1.0 / s.z;
            shape.setPosition(s.position*scale+conf::window_size_f*0.5f);
            shape.setScale(scale, scale);
            window.draw(shape);
        }

        window.display();

    }

    return 0;
}