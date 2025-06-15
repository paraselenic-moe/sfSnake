#include <SFML/Graphics.hpp>

#include <cmath>

#include "../Core/Game.h"
#include "../Entities/Fruit.h"
#include "../Entities/Snake.h"
#include "../Entities/SnakeNode.h"
#include "SFML/System/Vector2.hpp"

using namespace sfSnake;

const size_t Snake::InitialSize = 5;

sf::SoundBuffer Snake::pickupBuffer;
sf::Sound Snake::pickupSound;
sf::SoundBuffer Snake::dieBuffer;
sf::Sound Snake::dieSound;

float getDistance(const sf::Vector2f& a, const sf::Vector2f& b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

void Snake::loadSound() {
    pickupBuffer.loadFromFile("Assets/pickup.wav");
    pickupSound.setBuffer(pickupBuffer);
    pickupSound.setVolume(30);

    dieBuffer.loadFromFile("Assets/die.wav");
    dieSound.setBuffer(dieBuffer);
    dieSound.setVolume(50);
}

Snake::Snake() : direction(-0.5 * M_PI), hitSelfFlag(false) { initNodes(); }

void Snake::initNodes() {
    for (size_t i = 0; i < (Snake::InitialSize - 1) * Game::TicksPerNode + 1; i++)
        nodes.push_back(SnakeNode(sf::Vector2f(Game::Width / 2., Game::Height / 2. + SnakeNode::Radius * 2 * i)));
}

bool Snake::handleInput(sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        direction = atan2(mousePos.y - nodes[0].getPosition().y, mousePos.x - nodes[0].getPosition().x);
    }
    return false;
}

void Snake::update(sf::Time delta) {
    move();
    checkEdgeCollisions();
    checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits) {
    SnakeNode& headNode = nodes[0];
    for (auto it = fruits.begin(); it != fruits.end();)
        if (getDistance(headNode.getPosition(), it->getPosition()) <= SnakeNode::RenderRadius + Fruit::Radius) {
            pickupSound.play();
            grow(it->getGrow());
            it = fruits.erase(it);
        } else
            it++;
}

void Snake::grow(size_t len) {
    sf::Vector2f position = nodes.back().getPosition();
    for (size_t i = 0; i < len * Game::TicksPerNode; i++) nodes.push_back(position);
}

size_t Snake::getSize() const { return nodes.size(); }

bool Snake::hitSelf() const { return hitSelfFlag; }

void Snake::checkSelfCollisions() {
    SnakeNode& headNode = nodes[0];
    for (size_t i = Game::TicksPerNode * 2.5; i < nodes.size(); ++i)
        if (getDistance(headNode.getPosition(), nodes[i].getPosition()) <= SnakeNode::RenderRadius) {
            dieSound.play();
            sf::sleep(sf::seconds(dieBuffer.getDuration().asSeconds()));
            hitSelfFlag = true;
            return;
        }
}

void Snake::checkEdgeCollisions() {
    SnakeNode& headNode = nodes[0];
    if (headNode.getPosition().x <= 0)
        headNode.setPosition(Game::Width, headNode.getPosition().y);
    else if (headNode.getPosition().x >= Game::Width)
        headNode.setPosition(0, headNode.getPosition().y);
    else if (headNode.getPosition().y <= 0)
        headNode.setPosition(headNode.getPosition().x, Game::Height);
    else if (headNode.getPosition().y >= Game::Height)
        headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::move() {
    for (size_t i = nodes.size() - 1; i > 0; i--) nodes[i].setPosition(nodes.at(i - 1).getPosition());

    nodes[0].move(std::cos(direction) * 2 * SnakeNode::Radius, std::sin(direction) * 2 * SnakeNode::Radius);
}

void Snake::render(sf::RenderWindow& window) {
    for (size_t i = nodes.size() - 1; i > 0; i -= Game::TicksPerNode) {
        float direction = atan2(nodes[i].getPosition().y - nodes[i - Game::TicksPerNode].getPosition().y,
                                nodes[i].getPosition().x - nodes[i - Game::TicksPerNode].getPosition().x);
        nodes[i].render(window, direction, false);
    }
    nodes[0].render(window, direction, true);
}
