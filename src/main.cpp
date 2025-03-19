#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>



int main() {

    auto window = sf::RenderWindow({ 800, 600 }, "SFML works!");
    window.setFramerateLimit(60);

    // sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    // Declare an sf::Event object
    sf::Event event;


    while (window.isOpen()) {
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

        window.clear();
        window.display();

    }

    return 0;
}