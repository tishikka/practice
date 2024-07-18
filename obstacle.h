#ifndef OBSTACLE
#define OBSTACLE

#include <SFML/Graphics.hpp>

class Obstacle {
public:
    sf::RectangleShape shape;
    bool passed;

    Obstacle();

    void update();

    void setPosition(float x, float y);
};

#endif
