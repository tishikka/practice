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
    void reset();
private:
    bool isJumping;
    float jumpHeight;
};

#endif