#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake {
class Fruit {
   public:
    Fruit(sf::Vector2f position = sf::Vector2f(0, 0));

    void render(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;

   private:
    static const float Radius;

    sf::Vector2f position;
};
}  // namespace sfSnake

#endif