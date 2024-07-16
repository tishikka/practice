#ifndef PLAYER
#define PLAYER

#include <SFML/Graphics.hpp>

class Player {
public:
    sf::RectangleShape shape;
    sf::Texture texture;

    Player();
    void jump();
    void update();
private:
    bool isJumping;
    float jumpHeight;
};

#endif