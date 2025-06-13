#include <SFML/Graphics.hpp>

#include <memory>

#include "../Core/Game.h"
#include "../Screens/GameScreen.h"
#include "../Screens/MenuScreen.h"

using namespace sfSnake;

MenuScreen::MenuScreen() {
    font.loadFromFile("Fonts/game_over.ttf");
    text.setFont(font);
    text.setString(
        "\n\n\n\n\n\n\n\n\nPress [SPACE] to play"
        "\n\nPress [ESC] to quit");

    snakeText.setFont(font);
    snakeText.setString("Snake!");
    snakeText.setFillColor(sf::Color::Green);
    snakeText.setCharacterSize(64);
    snakeText.setStyle(sf::Text::Bold);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    text.setPosition(Game::Width / 2., Game::Height / 2.);

    sf::FloatRect snakeTextBounds = snakeText.getLocalBounds();
    snakeText.setOrigin(snakeTextBounds.left + snakeTextBounds.width / 2, snakeTextBounds.top + snakeTextBounds.height / 2);
    snakeText.setPosition(Game::Width / 2., Game::Height / 4.);
}

bool MenuScreen::handleInput(sf::RenderWindow& window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        Game::screen = std::make_shared<GameScreen>();
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
        return true;
    }
    return false;
}

void MenuScreen::update(sf::Time delta) {
    static bool movingLeft = false;
    static bool movingRight = true;

    if (movingRight) {
        snakeText.rotate(delta.asSeconds());

        if (static_cast<int>(snakeText.getRotation()) == 10) {
            movingRight = false;
            movingLeft = true;
        }
    }

    if (movingLeft) {
        snakeText.rotate(-delta.asSeconds());

        if (static_cast<int>(snakeText.getRotation()) == (360 - 10)) {
            movingLeft = false;
            movingRight = true;
        }
    }
}

void MenuScreen::render(sf::RenderWindow& window) {
    window.draw(text);
    window.draw(snakeText);
}