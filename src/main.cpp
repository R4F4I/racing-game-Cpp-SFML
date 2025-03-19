#include <SFML/Graphics.hpp>
#include <iostream>


enum dir
{
    down,up,left,right
};

int main()
{
    float height = 600;
    float width = 800;
    auto window = sf::RenderWindow(sf::VideoMode({800, 600}), "CMake SFML Project");
    window.setFramerateLimit(14);

    sf::Texture textire;

    if (!textire.loadFromFile("Sprites/img_navsprites.gif"))
    {
        std::cerr << "eror " << std::endl;
        return -1;
    }

    sf::Sprite sprite(textire);
    sf::IntRect dir[4];

    for (size_t i = 0; i < 4; i++)
    {
        dir[i] = sf::IntRect({ {32 * i,0},{32,32} });
    }

    sprite.setTextureRect(dir[down]);
    sprite.setOrigin({ 16,16 });
    sprite.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f));

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (const auto keyPressed = event.getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    window.close();
                }
            }
        }

        window.clear();

        window.draw(sprite);


        /*sf::CircleShape c{100.0f};
        c.setFillColor(sf::Color::Blue);
        window.draw(c);*/

        window.display();



    }
    return 0;

}
