#include <TGUI/TGUI.hpp>

sf::RenderWindow window(sf::VideoMode(800, 600), "Game Menu");
tgui::Gui gui(window);

auto button = tgui::Button::create("Play");
button->setPosition(300, 250);
button->setSize(200, 50);
gui.add(button);

button->onPress([]() {
    std::cout << "Play button pressed!" << std::endl;
});

while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
        gui.handleEvent(event);
        if (event.type == sf::Event::Closed)
            window.close();
    }

    window.clear();
    gui.draw();
    window.display();
}
