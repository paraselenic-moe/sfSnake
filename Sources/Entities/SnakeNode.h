#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake {
class SnakeNode {
   public:
    SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0));

    void setPosition(sf::Vector2f position);
    void setPosition(float x, float y);

    void move(float xOffset, float yOffset);

    void render(sf::RenderWindow& window, float direction, bool isHead);

    sf::Vector2f getPosition() const;

    static const float Radius;
    static const float RenderRadius;

    static void loadTexture();

   private:
    sf::Vector2f position;
    float angle;

    static sf::Texture snakeHeadTexture;
    static sf::Texture snakeBodyTexture;
};
}  // namespace sfSnake

#endif