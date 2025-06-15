#include "Core/Game.h"
#include "Entities/Snake.h"
#include "Entities/SnakeNode.h"

using namespace sfSnake;

int main() {
    Snake::loadSound();
    SnakeNode::loadTexture();

    Game game;
    game.run();

    return 0;
}