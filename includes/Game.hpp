#pragma once

#include <string>
#include "LifeState.hpp"

class Game {

private:
    static const int FPS;
    static const int SKIP_TICKS;
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
