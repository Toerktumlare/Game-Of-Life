#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "GameData.hpp"
#include "Grid.hpp"

class LifeState {
public:
    bool isGenerating;
private:
    Grid<bool> nextState;
    Grid<bool> currentState;
    Grid<sf::Sprite> sprites;
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
    int getNeighbours(const int x, const int y);
    void updateCell(const int height, const int width, const int neighbours);
};
