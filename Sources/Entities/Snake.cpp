#include <SFML/Graphics.hpp>

#include <cmath>
#include <iostream>

#include "../Core/Game.h"
#include "../Entities/Fruit.h"
#include "../Entities/Snake.h"
#include "../Entities/SnakeNode.h"

using namespace sfSnake;

const size_t Snake::InitialSize = 5;

float getDistance(const sf::Vector2f& a, const sf::Vector2f& b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

Snake::Snake() : direction(Direction::Up), hitSelfFlag(false) {
    initNodes();

    pickupBuffer.loadFromFile("Sounds/pickup.aiff");
    pickupSound.setBuffer(pickupBuffer);
    pickupSound.setVolume(30);

    dieBuffer.loadFromFile("Sounds/die.wav");
    dieSound.setBuffer(dieBuffer);
    dieSound.setVolume(50);
}

void Snake::initNodes() {
    for (size_t i = 0; i < (Snake::InitialSize - 1) * Game::TicksPerNode + 1; i++) {
        nodes.push_back(SnakeNode(sf::Vector2f(Game::Width / 2., Game::Height / 2. + SnakeNode::Radius * 2 * i)));
    }
}

bool Snake::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        direction = Direction::Up;
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        direction = Direction::Down;
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction = Direction::Left;
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction = Direction::Right;
        return true;
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

    bool pickup = false;
    int growLength = 0;

    for (auto it = fruits.begin(); it != fruits.end();)
        if (getDistance(headNode.getPosition(), it->getPosition()) <= SnakeNode::RenderRadius + Fruit::Radius) {
            pickup = true;
            growLength++;  // TODO
            it = fruits.erase(it);
        } else
            it++;

    if (pickup) {
        pickupSound.play();
        grow(growLength);
    }
}

void Snake::grow(size_t len) {
    for (size_t i = 0; i < len * Game::TicksPerNode; i++) {
        switch (direction) {
            case Direction::Up:
                nodes.push_back(SnakeNode(sf::Vector2f(nodes[nodes.size() - 1].getPosition().x,
                                                       nodes[nodes.size() - 1].getPosition().y + 2 * SnakeNode::Radius)));
                break;
            case Direction::Down:
                nodes.push_back(SnakeNode(sf::Vector2f(nodes[nodes.size() - 1].getPosition().x,
                                                       nodes[nodes.size() - 1].getPosition().y - 2 * SnakeNode::Radius)));
                break;
            case Direction::Left:
                nodes.push_back(SnakeNode(sf::Vector2f(nodes[nodes.size() - 1].getPosition().x + 2 * SnakeNode::Radius,
                                                       nodes[nodes.size() - 1].getPosition().y)));
                break;
            case Direction::Right:
                nodes.push_back(SnakeNode(sf::Vector2f(nodes[nodes.size() - 1].getPosition().x - 2 * SnakeNode::Radius,
                                                       nodes[nodes.size() - 1].getPosition().y)));
                break;
        }
    }
}

size_t Snake::getSize() const { return nodes.size(); }

bool Snake::hitSelf() const { return hitSelfFlag; }

void Snake::checkSelfCollisions() {
    SnakeNode& headNode = nodes[0];

    for (size_t i = Game::TicksPerNode * 2; i < nodes.size(); ++i)
        if (getDistance(headNode.getPosition(), nodes[i].getPosition()) <= SnakeNode::RenderRadius) {
            dieSound.play();
            sf::sleep(sf::seconds(dieBuffer.getDuration().asSeconds()));
            hitSelfFlag = true;
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
    // !

    for (size_t i = nodes.size() - 1; i > 0; i--) nodes[i].setPosition(nodes.at(i - 1).getPosition());

    switch (direction) {
        case Direction::Up:
            nodes[0].move(0, -2 * SnakeNode::Radius);
            break;
        case Direction::Down:
            nodes[0].move(0, 2 * SnakeNode::Radius);
            break;
        case Direction::Left:
            nodes[0].move(-2 * SnakeNode::Radius, 0);
            break;
        case Direction::Right:
            nodes[0].move(2 * SnakeNode::Radius, 0);
            break;
    }
}

void Snake::render(sf::RenderWindow& window) {
    // TODO Snake head render

    for (size_t i = 0; i < nodes.size(); i += Game::TicksPerNode) nodes[i].render(window);
}
