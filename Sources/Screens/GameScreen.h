#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>

#include "../Entities/Fruit.h"
#include "../Entities/Snake.h"
#include "../Screens/Screen.h"

namespace sfSnake {
class GameScreen : public Screen {
   public:
    GameScreen();

    bool handleInput(sf::RenderWindow& window) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;

    void generateFruit();

   private:
    Snake snake;
    std::vector<Fruit> fruits;

    static const size_t MaxFruitsNum;
};
}  // namespace sfSnake

#endif