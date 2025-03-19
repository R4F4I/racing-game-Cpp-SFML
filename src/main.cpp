#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include "events.hpp"
#include "configuration.hpp"
#include "stars.hpp"


std::vector<Star> createStars(uint32_t count, float scale) {
    std::vector<Star> stars;
    stars.reserve(count);

    // random num generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    // create randomly distributed stars on screen
    for (uint32_t i{ count };i--;) {
        // added 0.5 center all the values, because the starting values in the window start from top right
        float const x = (dis(gen) - 0.5f) * conf::window_size_f.x * scale;
        float const y = (dis(gen) - 0.5f) * conf::window_size_f.y * scale;

        // random depth z for each star
        float const z = dis(gen) * (conf::far - conf::near)+conf::near;


        stars.push_back({{x,y},z});
    }

    // depth ordering
    std::sort(stars.begin(), stars.end(), [](Star const& s_1, Star const& s_2) {
        return s_1.z > s_2.z;

        });

    return stars;
}


int main() {

    auto window = sf::RenderWindow({conf::window_size.x,conf::window_size.y}, "SFML works!");
    window.setFramerateLimit(conf::max_framerate);

    // sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    std::vector<Star> stars = createStars(conf::count,conf::far);

    uint32_t first = 0;

    while (window.isOpen()) {
        
        processEvents(window);

        // fake travel toward increasing Z


        for (uint32_t i{ conf::count };i--;) // for loop update is reversed to deal with a bug
        {
            Star &s = stars[i];
            s.z -= conf::speed * conf::dt;

            // circling the stars to the back as after being less than conf::near they just disappear, 
            if (s.z<conf::near)
            {
                // offset the star excess travel it made to keep spacing constant
                s.z = conf::far - (conf::near - s.z);

                // the star that has been circled back will still have a large z value
                // we will draw further away stars first so the closer ones can overlap them
                first = i;
            }
        }

        // rendering occurs here 
        window.clear();

        sf::CircleShape shape{ conf::radius };
        shape.setOrigin(conf::radius, conf::radius);

        for (uint32_t i{ 0 };i < conf::count;++i)
        {
            // visibility no longer needed 
            
            uint32_t const idx = (i + first) % conf::count;
            Star const& s = stars[idx];

            // inverse because more depth, lesser the scale
            float const scale = 1.0 / s.z;
            shape.setPosition(s.position*scale+conf::window_size_f*0.5f);
            shape.setScale(scale, scale);


            float const depth_ratio = (s.z - conf::near) / (conf::far - conf::near);
            float const color_ratio = 1-depth_ratio;
            auto const c = static_cast<uint8_t>(color_ratio * 255.0f);
            shape.setFillColor({ c,c,c });


            window.draw(shape);
            
        }

        window.display();

    }

    return 0;
}