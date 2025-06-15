#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake {
class Fruit {
   public:
    Fruit(sf::Vector2f position = sf::Vector2f(0, 0));

    void render(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;

    int getGrow() const;

    static const float Radius;

   private:
    enum ColorOption { Black, Brown, Red, Blue, Green };

    sf::Color getColorFromOption(ColorOption option) const;

    sf::Vector2f position;
    ColorOption color;
};
}  // namespace sfSnake

#endif