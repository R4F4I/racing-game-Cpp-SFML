#include "events.hpp"


void processEvents(sf::Window& window ){
    // Declare an sf::Event object
    sf::Event event;
    
    while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }
}