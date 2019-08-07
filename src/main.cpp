#include "Game.hpp"
#include "OpenGame.hpp"

int main()
{
    Game game = OpenGame("Game of Life")
        .cellHeight(32)
        .cellWidth(64);
    game.run();
}
