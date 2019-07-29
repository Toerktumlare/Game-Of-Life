#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "GameData.hpp"

class LifeState {
public:
    bool isGenerating;
private:
    std::vector<std::vector<bool>> nextState;
    std::vector<std::vector<bool>> currentState;
    std::vector<std::vector<sf::Sprite>> sprites;;
    GameDataRef data;
    int lastTime;
    sf::Clock clock;
    
public:
    void init(GameDataRef &data);
        
    void toggle(sf::Vector2<float> translated_pos);
    
    void start();
    
    void stop();
    
    void update();
    
    void draw();
    
private:
    void updateCell(int height, int width, int neighbours);
};
