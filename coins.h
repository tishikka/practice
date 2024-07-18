#ifndef COIN_COLLECTOR
#define COIN_COLLECTOR

class Coin {
private:
    int coinsCollected;

public:
    CoinCollector();
    void collectCoin();
    int getCoinsCollected();
    void reset();  // Добавляем метод для сброса счетчика монет
};

#endif
