#include "background.h"

Background::Background() {
    shape.setSize(sf::Vector2f(1280, 720));
    texture.loadFromFile("foto/sky.png");
    shape.setTexture(&texture);
    shape.setPosition(sf::Vector2f(0, 0));
}

void Background::update() {
    shape.move(sf::Vector2f(-2.5, 0));
    if (shape.getPosition().x <= -1280) {
        shape.setPosition(1280, 0);
    }
}