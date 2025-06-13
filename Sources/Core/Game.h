#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <memory>

#include "../Screens/BgScreen.h"
#include "../Screens/Screen.h"

namespace sfSnake {
class Game {
   public:
    Game();

    void run();

    void handleInput();
    void update(sf::Time delta);
    void render();

    static const int Width = 1920;
    static const int Height = 1440;

    static const int TPS = 60;
    static const int TicksPerNode = 8;

    static std::shared_ptr<Screen> screen;
    static std::shared_ptr<BgScreen> bgScreen;

   private:
    sf::RenderWindow window;
    sf::Music bgMusic;

    static const sf::Time TimePerFrame;
};
}  // namespace sfSnake

#endif