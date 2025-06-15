#include <SFML/Graphics.hpp>

#include <memory>

#include "../Core/Game.h"
#include "../Screens/BgScreen.h"
#include "../Screens/MenuScreen.h"

using namespace sfSnake;

const sf::Time Game::TimePerFrame = sf::seconds(1. / Game::TPS);

std::shared_ptr<Screen> Game::screen = std::make_shared<MenuScreen>();
std::shared_ptr<BgScreen> Game::bgScreen = std::make_shared<BgScreen>();

Game::Game() : window(sf::VideoMode(Game::Width, Game::Height), "Snake") {
    bgMusic.openFromFile("Assets/MyGO!!!!!.ogg");
    bgMusic.setLoop(true);
    bgMusic.play();
}

void Game::handleInput() {
    sf::Event event;
    while (window.pollEvent(event))
        if (event.type == sf::Event::Closed) window.close();

    if (screen->handleInput(window)) return;
    if (bgScreen->handleInput(window)) return;
}

void Game::update(sf::Time delta) { screen->update(delta); }

void Game::render() {
    window.clear();
    bgScreen->render(window);
    screen->render(window);
    window.display();
}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen()) {
        do {
            sf::sleep(sf::milliseconds(1));
            sf::Time delta = clock.restart();
            timeSinceLastUpdate += delta;
        } while (timeSinceLastUpdate < TimePerFrame);

        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            handleInput();
            update(TimePerFrame);
        }

        render();
    }
}