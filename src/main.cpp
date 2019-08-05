#include "Game.hpp"

int main()
{
    auto game = Game()
        .setHeight(2048)
        .setWidth(2048)
        .setTitle("Conways game of life");
    game.run();
}
