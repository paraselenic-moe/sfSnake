#include <SFML/Graphics.hpp>

#include <random>

#include "../Core/Game.h"
#include "../Screens/GameOverScreen.h"
#include "../Screens/GameScreen.h"

using namespace sfSnake;

const size_t GameScreen::MaxFruitsNum = 8;

GameScreen::GameScreen() {}

bool GameScreen::handleInput(sf::RenderWindow& window) {
    if (snake.handleInput(window)) return true;
    return false;
}

void GameScreen::update(sf::Time delta) {
    while (fruits.size() < MaxFruitsNum) generateFruit();

    snake.update(delta);
    snake.checkFruitCollisions(fruits);

    if (snake.hitSelf()) Game::screen = std::make_shared<GameOverScreen>((snake.getSize() - 1) / Game::TicksPerNode + 1);
}

void GameScreen::render(sf::RenderWindow& window) {
    snake.render(window);
    for (auto& fruit : fruits) fruit.render(window);
}

void GameScreen::generateFruit() {
    static std::default_random_engine engine(time(NULL));
    static std::uniform_int_distribution<int> xDistribution(Fruit::Radius, Game::Width - Fruit::Radius);
    static std::uniform_int_distribution<int> yDistribution(Fruit::Radius, Game::Height - Fruit::Radius);

    fruits.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine))));
}
