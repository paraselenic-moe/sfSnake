#include <SFML/Graphics.hpp>

#include <cmath>

#include "../Core/Game.h"
#include "../Entities/SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Radius = 2;
const float SnakeNode::RenderRadius = Radius * Game::TicksPerNode * 1.4;

sf::Texture SnakeNode::snakeHeadTexture;
sf::Texture SnakeNode::snakeBodyTexture;

void SnakeNode::loadTexture() {
    snakeHeadTexture.loadFromFile("Assets/SnakeHead.png");
    snakeBodyTexture.loadFromFile("Assets/SnakeBody.png");
}

SnakeNode::SnakeNode(sf::Vector2f position) : position(position) {}

void SnakeNode::setPosition(sf::Vector2f position) { this->position = position; }

void SnakeNode::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

void SnakeNode::move(float xOffset, float yOffset) {
    position.x += xOffset;
    position.y += yOffset;
}

sf::Vector2f SnakeNode::getPosition() const { return position; }

void SnakeNode::render(sf::RenderWindow& window, float direction, bool isHead) {
    sf::Sprite sprite;
    sprite.setTexture(isHead ? snakeHeadTexture : snakeBodyTexture);
    sprite.setScale(RenderRadius * 2.6 / snakeHeadTexture.getSize().x, RenderRadius * 2.6 / snakeHeadTexture.getSize().y);
    sprite.setOrigin(sprite.getTexture()->getSize().x / 2., sprite.getTexture()->getSize().y / 2.);
    sprite.setPosition(position);
    sprite.rotate((direction * 180 / M_PI) - 90);
    window.draw(sprite);
}