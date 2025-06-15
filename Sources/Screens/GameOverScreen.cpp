#include <SFML/Graphics.hpp>

#include <memory>

#include "../Core/Game.h"
#include "../Screens/GameScreen.h"
#include "../Screens/GameOverScreen.h"

using namespace sfSnake;

GameOverScreen::GameOverScreen(std::size_t score) : score_(score) {
    font_.loadFromFile("Assets/font.ttf");
    text_.setFont(font_);
    text_.setString("Your score: " + std::to_string(score) +
                    "!"
                    "\n\nPress [SPACE] to retry"
                    "\n\nPress [ESC] to quit");
    text_.setFillColor(sf::Color::Red);

    sf::FloatRect textBounds = text_.getLocalBounds();
    text_.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    text_.setPosition(Game::Width / 2., Game::Height / 2.);
}

bool GameOverScreen::handleInput(sf::RenderWindow& window) {
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

void GameOverScreen::update(sf::Time delta) {}

void GameOverScreen::render(sf::RenderWindow& window) { window.draw(text_); }