#include "obstacle.h"

Obstacle::Obstacle() : passed(false) {
    shape.setSize(sf::Vector2f(50, 50));  // Размер препятствия
    shape.setFillColor(sf::Color::Red);   // Цвет препятствия
}

void Obstacle::update() {
    shape.move(-5.0f, 0);  // Движение препятствия влево
}

void Obstacle::setPosition(float x, float y) {
    shape.setPosition(x, y);
}
