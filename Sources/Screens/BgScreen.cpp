#include "../Screens/BgScreen.h"

using namespace sfSnake;

const float BgScreen::GridSize = 48.f;

BgScreen::BgScreen() : backgroundColor(ColorOption::Black), gridColor(ColorOption::None) {}

bool BgScreen::handleInput(sf::RenderWindow& window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        backgroundColor = ColorOption::White;
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        backgroundColor = ColorOption::Black;
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
        backgroundColor = ColorOption::Brown;
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
        gridColor = ColorOption::None;
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
        gridColor = ColorOption::White;
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {
        gridColor = ColorOption::Black;
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) {
        gridColor = ColorOption::Brown;
        return true;
    }
    return false;
}

void BgScreen::update(sf::Time delta) {}

void BgScreen::render(sf::RenderWindow& window) {
    sf::RectangleShape background(sf::Vector2f(window.getSize()));
    background.setFillColor(getColorFromOption(backgroundColor));
    window.draw(background);

    if (gridColor == ColorOption::None) return;

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

sf::Color BgScreen::getColorFromOption(ColorOption option) {
    switch (option) {
        case ColorOption::White:
            return sf::Color::White;
        case ColorOption::Brown:
            return sf::Color(139, 69, 19);
        case ColorOption::Black:
            return sf::Color::Black;
        default:
            return sf::Color::White;
    }
}