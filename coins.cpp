#include "coins.h"

Coin::Coin() {
    shape.setSize(sf::Vector2f(120, 60));
    textureCoin.loadFromFile("D:/Programming/project5/foto/coin.png");
    shape.setTexture(&textureCoin);
    collected = false;
}

void Coin::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

CoinCollector::CoinCollector() {
    coinsCollected = 0;
}

void CoinCollector::collectCoin() {
    coinsCollected++;
}

int CoinCollector::getCoinsCollected() {
    return coinsCollected;
}
