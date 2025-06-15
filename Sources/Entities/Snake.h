#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "../Entities/SnakeNode.h"
#include "../Entities/Fruit.h"

namespace sfSnake {
class Snake {
   public:
    Snake();

    bool handleInput(sf::RenderWindow& windows);
    void update(sf::Time delta);
    void render(sf::RenderWindow& window);

    void checkFruitCollisions(std::vector<Fruit>& fruits);

    bool hitSelf() const;

    size_t getSize() const;

    static void loadSound();

   private:
    void move();
    void grow(size_t len);
    void checkEdgeCollisions();
    void checkSelfCollisions();
    void initNodes();

    bool hitSelfFlag;

    sf::Vector2f position;
    float direction;

    std::vector<SnakeNode> nodes;

    static const size_t InitialSize;

    static sf::SoundBuffer pickupBuffer;
    static sf::Sound pickupSound;
    static sf::SoundBuffer dieBuffer;
    static sf::Sound dieSound;
};
}  // namespace sfSnake

#endif