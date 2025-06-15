#include "../Screens/BgScreen.h"

using namespace sfSnake;

const float BgScreen::GridSize = 48;

BgScreen::BgScreen() : backgroundColor(Black), gridColor(None) {}

bool BgScreen::handleInput(sf::RenderWindow& window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        backgroundColor = White;
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        backgroundColor = Black;
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
        backgroundColor = Brown;
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
        gridColor = None;
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
        gridColor = White;
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {
        gridColor = Black;
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) {
        gridColor = Brown;
        return true;
    }
    return false;
}

void BgScreen::update(sf::Time delta) {}

void BgScreen::render(sf::RenderWindow& window) {
    sf::RectangleShape background(sf::Vector2f(window.getSize()));
    background.setFillColor(getColorFromOption(backgroundColor));
    window.draw(background);

    sf::Vector2u size = window.getSize();
    size_t rows = size.y / GridSize;
    size_t cols = size.x / GridSize;

    sf::Vertex line[2];
    line[0].color = line[1].color = getColorFromOption(gridColor);

    for (size_t i = 0; i <= rows; i++) {
        float y = i * GridSize;
        line[0].position = sf::Vector2f(0, y);
        line[1].position = sf::Vector2f(size.x, y);
        window.draw(line, 2, sf::Lines);
    }
    for (size_t i = 0; i <= cols; i++) {
        float x = i * GridSize;
        line[0].position = sf::Vector2f(x, 0);
        line[1].position = sf::Vector2f(x, size.y);
        window.draw(line, 2, sf::Lines);
    }
}

sf::Color BgScreen::getColorFromOption(ColorOption option) const {
    if (option == None) return sf::Color(0, 0, 0, 0);
    if (option == White) return sf::Color::White;
    if (option == Brown) return sf::Color(139, 69, 19);
    if (option == Black) return sf::Color::Black;
    return sf::Color(0, 0, 0, 0);
}