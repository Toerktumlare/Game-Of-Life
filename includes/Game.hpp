#pragma once

#include <string>
#include "LifeState.hpp"

class Game {

private:
    static const int FPS;
    static const int SKIP_TICKS;
    sf::Clock clock;
    GameDataRef data = std::make_shared<GameData>();
    LifeState lifeState;
    
public:
    Game(const int width, const int height, const std::string title);
    
    void run();
    
    void updateGame();
    
    void displayGame();
    
private:
    void handleKeyCode(sf::Keyboard::Key key);
    
};
