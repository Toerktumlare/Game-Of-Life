#pragma once

#include <string_view>
#include <chrono>

#include "LifeState.hpp"


using fps_t = int;

class Game {

private:
    static constexpr fps_t fps = 25;
    static constexpr std::chrono::duration<int, std::ratio<1, 1000>> skip_ticks = std::chrono::milliseconds(1000 / fps);
    int height;
    int width;
    std::string_view title;
    sf::Clock clock;
    GameDataRef data = std::make_shared<GameData>();
    LifeState lifeState;
    
public:
    Game();
    
    Game& setHeight(const int height);
    Game& setWidth(const int width);
    Game& setTitle(const std::string_view title);


    void run();
    
    void updateGame();
    
    void displayGame();
    
private:
    void handleKeyCode(sf::Keyboard::Key key);
    
    
};
