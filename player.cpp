#include "player.h"

Player::Player() {
    shape.setSize(sf::Vector2f(100, 100));
    texture.loadFromFile("D:/Programming/project5/foto/running.png");
    shape.setTexture(&texture);
    shape.setPosition(sf::Vector2f(50, 570));
    isJumping = false;
    jumpHeight = 0;
}

void Player::jump() {
    if (!isJumping) {
        isJumping = true;
    }
}

void Player::update() {
    if (isJumping) {
        if (jumpHeight < 100) {
            shape.move(0, -5);
            jumpHeight += 5;
        } else {
            isJumping = false;
        }
    } else if (shape.getPosition().y < 570) {
        shape.move(0, 5);
    }
}

void Player::reset() {
    shape.setPosition(sf::Vector2f(50, 570));
    isJumping = false;
    jumpHeight = 0;
}
