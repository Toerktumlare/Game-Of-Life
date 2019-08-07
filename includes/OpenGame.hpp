# pragma once

#include <string>
#include "Game.hpp"

class OpenGame {
private:
    friend class Game;
    std::string_view title_;
    unsigned int cellHeight_;
    unsigned int cellWidth_;

public:
    OpenGame(const std::string_view& title);
    OpenGame& cellHeight(const unsigned int cellHeight);
    OpenGame& cellWidth(const unsigned int cellWidth);
};

inline OpenGame::OpenGame(const std::string_view& title) : title_("Game Of Life"), cellHeight_(128), cellWidth_(128)
{ };

inline OpenGame& OpenGame::cellHeight(const unsigned int cellHeight)
{
    this->cellHeight_ = cellHeight;
    return *this;
}

inline OpenGame& OpenGame::cellWidth(const unsigned int cellWidth)
{
    this->cellWidth_ = cellWidth;
    return *this;
}
