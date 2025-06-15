#include <SFML/Graphics.hpp>

#include <random>

#include "../Entities/Fruit.h"

using namespace sfSnake;

const float Fruit::Radius = 12;

Fruit::Fruit(sf::Vector2f position) {
    this->position = position;

    static std::default_random_engine engine(time(NULL));
    static std::uniform_int_distribution<int> colorDistribution(0, 7);
    int colorId = colorDistribution(engine);
    if (colorId == 0) this->color = Black;
    if (colorId == 1) this->color = Brown;
    if (colorId >> 1 == 1) this->color = Red;
    if (colorId >> 1 == 2) this->color = Blue;
    if (colorId >> 1 == 3) this->color = Green;
}

void Fruit::render(sf::RenderWindow& window) {
    sf::CircleShape circle(Radius);
    circle.setFillColor(getColorFromOption(color));
    circle.setOutlineColor(sf::Color::White);
    circle.setOutlineThickness(-2);
    circle.setOrigin(Radius, Radius);
    circle.setPosition(position);
    window.draw(circle);
}

sf::Vector2f Fruit::getPosition() const { return position; }

int Fruit::getGrow() const {
    if (color == Black) return 0;
    if (color == Brown) return 0;
    if (color == Red) return 3;
    if (color == Blue) return 2;
    if (color == Green) return 1;
    return 0;
}

sf::Color Fruit::getColorFromOption(ColorOption option) const {
    if (option == Black) return sf::Color::Black;
    if (option == Brown) return sf::Color(139, 69, 19);
    if (option == Red) return sf::Color::Red;
    if (option == Blue) return sf::Color::Blue;
    if (option == Green) return sf::Color::Green;
    return sf::Color(0, 0, 0, 0);
}