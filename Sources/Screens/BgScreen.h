#ifndef BACKGROUND_SCREEN_H
#define BACKGROUND_SCREEN_H

#include "../Screens/Screen.h"

namespace sfSnake {

class BgScreen : public Screen {
   public:
    BgScreen();

    bool handleInput(sf::RenderWindow& window) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;

    static const float GridSize;

   private:
    enum ColorOption { None, White, Brown, Black };

    sf::Color getColorFromOption(ColorOption option) const;

    ColorOption backgroundColor;
    ColorOption gridColor;
};
}  // namespace sfSnake

#endif