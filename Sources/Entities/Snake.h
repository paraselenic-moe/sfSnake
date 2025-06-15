#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "../Entities/SnakeNode.h"
#include "../Entities/Fruit.h"

namespace sfSnake {
enum class Direction { Left, Right, Up, Down };

class Snake {
   public:
    Snake();

    bool handleInput();
    void update(sf::Time delta);
    void render(sf::RenderWindow& window);

    void checkFruitCollisions(std::vector<Fruit>& fruits);

    bool hitSelf() const;

    size_t getSize() const;

   private:
    void move();
    void grow(size_t len);
    void checkEdgeCollisions();
    void checkSelfCollisions();
    void initNodes();

    bool hitSelfFlag;

    sf::Vector2f position;
    Direction direction;

    sf::SoundBuffer pickupBuffer;
    sf::Sound pickupSound;

    sf::SoundBuffer dieBuffer;
    sf::Sound dieSound;

    std::vector<SnakeNode> nodes;

    static const size_t InitialSize;
};
}  // namespace sfSnake

#endif