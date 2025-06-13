#ifndef BACKGROUND_SCREEN_H
#define BACKGROUND_SCREEN_H

#include "../Screens/Screen.h"

namespace sfSnake {
enum class ColorOption { None, White, Brown, Black };

class BgScreen : public Screen {
   public:
    BgScreen();

    bool handleInput(sf::RenderWindow& window) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;

    static const float GridSize;

   private:
    sf::Color getColorFromOption(ColorOption option);

    ColorOption backgroundColor;
    ColorOption gridColor;
};
}  // namespace sfSnake

#endif