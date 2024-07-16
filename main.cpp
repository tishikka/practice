#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "player.h"
#include "coins.h"
#include "background.h"
#include "road.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), L"Endless runner");
    CoinCollector coinCollector;

    // Backgrounds
    Background gamingBackground;
    Background gamingBackground2;
    gamingBackground2.shape.setPosition(sf::Vector2f(1280, 0));

    // Road
    Road road;

    // Player
    Player player;

    sf::Clock clock;

    Coin coin1, coin2, coin3;
    coin1.setPosition(800, 570);
    coin2.setPosition(1200, 570);
    coin3.setPosition(1600, 570);

    Coin coinsArr[] = {coin1, coin2, coin3};

    srand(time(0));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float time = clock.getElapsedTime().asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            player.jump();
        }

        if (time > 0.01) {
            clock.restart();
            gamingBackground.update();
            gamingBackground2.update();
        }

        player.update();

        // Collect coins
        for (int i = 0; i < 3; i++) {
            if (!coinsArr[i].collected) {
                coinsArr[i].shape.move(sf::Vector2f(-2.5, 0));
            }

            if (player.shape.getGlobalBounds().intersects(coinsArr[i].shape.getGlobalBounds()) && !coinsArr[i].collected) {
                coinsArr[i].collected = true;
                coinCollector.collectCoin();
            }
        }

        window.clear();
        window.draw(gamingBackground.shape);
        window.draw(gamingBackground2.shape);
        window.draw(road.shape);

        for (int i = 0; i < 3; i++) {
            if (!coinsArr[i].collected) {
                window.draw(coinsArr[i].shape);
            }
        }

        window.draw(player.shape);

        // Display collected coins
        sf::Font font;
        font.loadFromFile("arial.ttf");
        sf::Text text;
        text.setFont(font);
        text.setString("Coins: " + std::to_string(coinCollector.getCoinsCollected()));
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition(10, 10);

        window.draw(text);
        window.display();
    }

    return 0;
}
