## **Project: Car Racing Game (2D) using SFML**

### **Project Overview:**

Create a **2D car racing game** where the player controls a car that must avoid obstacles and other vehicles while collecting power-ups. The game will use **SFML** (Simple and Fast Multimedia Library) for rendering graphics, handling user input, and playing sounds.

---

### **Key C++ Features Used:**

✅ **Classes & Object-Oriented Programming:** Cars, obstacles, power-ups, and the game engine will be represented as C++ classes.  
✅ **Inheritance & Polymorphism:** Different car types, obstacles, and power-ups will inherit from base classes.  
✅ **STL Containers & Algorithms:** Vectors for storing game objects, iterators for movement logic.  
✅ **File Handling:** Save and load high scores from a file.  
✅ **Multithreading (Optional):** Use a separate thread for background music.

---

### **Libraries Used:**

🔹 **SFML (Simple and Fast Multimedia Library)** – Handles graphics, window management, user input, and audio.  
🔹 **C++ STL** – Used for efficient data management.

---

## **Project Structure**

```
/CarRacingGame
│── main.cpp
│── Game.h/Game.cpp      // Main game loop and logic
│── Car.h/Car.cpp        // Player car class
│── Obstacle.h/Obstacle.cpp  // Obstacle class
│── PowerUp.h/PowerUp.cpp    // Power-up class
│── SFML-Dependencies/      // SFML libraries and assets
│── Assets/
│   ├── car.png
│   ├── track.png
│   ├── obstacle.png
│   ├── powerup.png
│   ├── background_music.ogg
│── Scores.txt        // Stores high scores
│── README.md
```

---

### **Class Design**

#### **1. `Car` Class (Base Class)**

```cpp
#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>

class Car {
protected:
    sf::Texture carTexture;
    sf::Sprite carSprite;
    float speed;
public:
    Car(const std::string& texturePath);
    void move(float x, float y);
    sf::Sprite getSprite() const;
};

#endif
```

#### **2. `PlayerCar` Class (Derived Class)**

```cpp
#ifndef PLAYER_CAR_H
#define PLAYER_CAR_H

#include "Car.h"

class PlayerCar : public Car {
public:
    PlayerCar(const std::string& texturePath);
    void handleInput();
};

#endif
```

#### **3. `Obstacle` Class**

```cpp
#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>

class Obstacle {
private:
    sf::Texture obstacleTexture;
    sf::Sprite obstacleSprite;
public:
    Obstacle(const std::string& texturePath, float x, float y);
    void moveDown(float speed);
    sf::Sprite getSprite() const;
};

#endif
```

#### **4. `Game` Class**

Handles the game loop, rendering, input handling, and collision detection.

```cpp
#ifndef GAME_H
#define GAME_H

#include "PlayerCar.h"
#include "Obstacle.h"
#include <vector>

class Game {
private:
    sf::RenderWindow window;
    PlayerCar player;
    std::vector<Obstacle> obstacles;
public:
    Game();
    void run();
    void processEvents();
    void update();
    void render();
};

#endif
```

---

## **Implementation Highlights**

1. **Game Loop:**
    - Processes user input
    - Updates game state (moving obstacles, checking collisions)
    - Renders graphics on the screen

2. **Collision Detection:**    
    - If the player's car collides with an obstacle, the game ends.
    - Uses SFML's **bounding box collision** detection.

3. **Scoring System:**
    - Distance traveled increases the score.
    - Save high scores to a text file using `fstream`.

4. **Graphics & Sound Effects:**
    - **SFML** is used to display textures for the car, road, obstacles, and background.
    - Background music plays in a loop using SFML’s `sf::Music`.

---

## **Example of `main.cpp`**

```cpp
#include "Game.h"

int main() {
    Game game;
    game.run();
    return 0;
}
```

---

### **Extra Features (Optional Enhancements)**

💡 **Power-ups:** Speed boost, shield, or coin collection for extra points.  
💡 **Multithreading:** Run background music in a separate thread.  
💡 **Different Cars:** Let the player choose from multiple car models.  
💡 **More Levels:** Add different difficulty levels with increasing obstacle density.

---

## **Why This is a Great C++ Project?**

✅ Uses **Object-Oriented Programming** principles  
✅ Implements **real-time graphics** using **SFML**  
✅ **File Handling** for saving high scores  
✅ Uses **STL Containers (vector)** for managing objects  
✅ **Collision Detection & Event Handling**
