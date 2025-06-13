#include <SFML/Graphics.hpp>

#include "../Entities/Fruit.h"

using namespace sfSnake;

const float Fruit::Radius = 15.;

Fruit::Fruit(sf::Vector2f position) { this->position = position; }

void Fruit::render(sf::RenderWindow& window) {
    sf::CircleShape circle(Radius);
    circle.setFillColor(sf::Color::Red);
    circle.setOrigin(Radius, Radius);
    circle.setPosition(position);
    window.draw(circle);
}

sf::Vector2f Fruit::getPosition() const { return position; }
