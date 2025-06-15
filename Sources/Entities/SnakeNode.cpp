#include <SFML/Graphics.hpp>

#include "../Core/Game.h"
#include "../Entities/SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Radius = 2;
const float SnakeNode::RenderRadius = Radius * Game::TicksPerNode * 1.4;

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

void SnakeNode::render(sf::RenderWindow& window) {
    sf::CircleShape circle(RenderRadius);
    circle.setFillColor(sf::Color::Yellow);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(-2);
    circle.setOrigin(RenderRadius, RenderRadius);
    circle.setPosition(position);
    window.draw(circle);
}