#pragma once

namespace conf
{
    // window configuration
    sf::Vector2u const window_size = { 1920,1080 };
    sf::Vector2f const window_size_f = static_cast<sf::Vector2f>(window_size);

    uint32_t const max_framerate = 60;
    float const dt = 1.0f / static_cast<float>(max_framerate);

    // The title of the window
    const char* windowTitle = "SFML Game";

    // star configuration

    uint32_t const count = 100000;

    float const radius = 8.0f;
    float const far = 7.0f;
    float const near = 1.0f;
    float const speed = 1.0f;
}