#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include <SFML/Graphics.hpp>

#include <memory>

#include "../Screens/Screen.h"

namespace sfSnake {
class MenuScreen : public Screen {
   public:
    MenuScreen();

    bool handleInput(sf::RenderWindow& window) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;

   private:
    sf::Font font;
    sf::Text snakeText;
    sf::Text text;

};
}  // namespace sfSnake

#endif