#ifndef BACKGROUND
#define BACKGROUND

#include <SFML/Graphics.hpp>

class Background {
public:
    sf::RectangleShape shape;
    sf::Texture texture;

    Background();
    void update();
};

#endif 
