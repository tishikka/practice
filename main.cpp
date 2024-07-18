#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include "player.h"
#include "coins.h"
#include "background.h"
#include "road.h"
#include "obstacle.h"

int main() {
    // Создание окна
    sf::RenderWindow window(sf::VideoMode(1280, 720), L"Endless runner");
    CoinCollector coinCollector;

    // Фоновые изображения
    Background gamingBackground;
    Background gamingBackground2;
    gamingBackground2.shape.setPosition(sf::Vector2f(1280, 0));

    // Дорога
    Road road;

    // Игрок
    Player player;

    sf::Clock clock;
    sf::Clock coinClock; // Для добавления новых монет
    sf::Clock obstacleClock; // Для добавления новых препятствий

    std::vector<Coin> coins;
    std::vector<Obstacle> obstacles;  // Вектор препятствий

    // Шрифт для отображения количества монет
    sf::Font font;
    bool fontLoaded = true;
    if (!font.loadFromFile("D:/Programming/project5/fonts/Josefin_Sans.ttf")) { // Убедитесь, что путь к шрифту правильный
        std::cerr << "Error loading font" << std::endl;
        fontLoaded = false; // Шрифт не загружен, продолжаем выполнение программы
    } else {
        std::cout << "Font loaded successfully" << std::endl;
    }

    sf::Text text;
    if (fontLoaded) {
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition(10, 10);
    }

    srand(static_cast<unsigned>(time(0)));

    bool gameOver = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (!gameOver) {
            float time = clock.getElapsedTime().asSeconds();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                player.jump();
            }

            if (time > 0.01f) {
                clock.restart();
                gamingBackground.update();
                gamingBackground2.update();
            }

            player.update();

            // Добавление новых монет
            if (coinClock.getElapsedTime().asSeconds() > 2) { // Каждые 2 секунды
                Coin newCoin;
                newCoin.setPosition(1280, 570);
                coins.push_back(newCoin);
                coinClock.restart();
                std::cout << "New coin added" << std::endl; // Отладочное сообщение
            }

            // Обновление и сбор монет
            for (auto& coin : coins) {
                if (!coin.collected) {
                    coin.shape.move(sf::Vector2f(-2.5f, 0));

                    if (player.shape.getGlobalBounds().intersects(coin.shape.getGlobalBounds())) {
                        coin.collected = true;
                        coinCollector.collectCoin();
                        std::cout << "Coin collected. Total: " << coinCollector.getCoinsCollected() << std::endl; // Отладочное сообщение
                    }
                }
            }

            // Удаление монет, которые вышли за левую границу
            coins.erase(std::remove_if(coins.begin(), coins.end(),
                [](const Coin& coin) {
                    return coin.shape.getPosition().x < -120;
                }), coins.end());

            // Добавление новых препятствий
            if (obstacleClock.getElapsedTime().asSeconds() > 3) { // Каждые 3 секунды
                Obstacle newObstacle;
                newObstacle.setPosition(1280, 570);
                obstacles.push_back(newObstacle);
                obstacleClock.restart();
                std::cout << "New obstacle added" << std::endl; // Отладочное сообщение
            }

            // Обновление препятствий
            for (auto& obstacle : obstacles) {
                if (!obstacle.passed) {
                    obstacle.update();

                    if (player.shape.getGlobalBounds().intersects(obstacle.shape.getGlobalBounds())) {
                        std::cout << "Collision with obstacle!" << std::endl; // Отладочное сообщение
                        gameOver = true;  // Устанавливаем флаг завершения игры
                        // Здесь можно добавить логику окончания игры или уменьшения здоровья игрока
                    }

                    if (obstacle.shape.getPosition().x < -50) {
                        obstacle.passed = true;
                    }
                }
            }

            // Удаление препятствий, которые вышли за левую границу
            obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(),
                [](const Obstacle& obstacle) {
                    return obstacle.shape.getPosition().x < -50;
                }), obstacles.end());
        } else { // Если игра окончена, то перезапускаем параметры
            // Обновляем все необходимые переменные и состояния
            gameOver = false;
            player.reset(); // Перезапуск игрока
            coins.clear(); // Очищаем все монеты
            obstacles.clear(); // Очищаем все препятствия
            coinCollector.reset(); // Сбрасываем счетчик монет
            clock.restart(); // Сбрасываем часы
            coinClock.restart(); // Сбрасываем часы для монет
            obstacleClock.restart(); // Сбрасываем часы для препятствий
        }

        window.clear();
        window.draw(gamingBackground.shape);
        window.draw(gamingBackground2.shape);
        window.draw(road.shape);

        for (const auto& coin : coins) {
            if (!coin.collected) {
                window.draw(coin.shape);
            }
        }

        for (const auto& obstacle : obstacles) {
            if (!obstacle.passed) {
                window.draw(obstacle.shape);
            }
        }

        window.draw(player.shape);

        // Обновление текста с количеством монет
        if (fontLoaded) {
            text.setString("Coins: " + std::to_string(coinCollector.getCoinsCollected()));
            window.draw(text);
        }

        window.display();
    }

    return 0;
}
