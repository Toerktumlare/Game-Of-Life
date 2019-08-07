#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "GameData.hpp"
#include <chrono>

class LifeState {
    
    typedef std::vector<std::vector<sf::Sprite>> Sprites;
    typedef std::vector<std::vector<bool>> State;
    
public:
    bool isGenerating;
private:
    State currentState;
    State nextState;
    Sprites sprites;
    GameDataRef data;
    std::chrono::duration<int, std::ratio<1, 1000>> lastTime = std::chrono::milliseconds{0};
    std::chrono::milliseconds acc_delta = std::chrono::milliseconds{0};
    sf::Clock clock;
    
public:
    LifeState();
    
    LifeState(size_t height, size_t width, GameDataRef &data);
        
    void toggle(sf::Vector2<float> translated_pos);
    
    void start();
    
    void stop();
    
    void update();
    
    void draw();
    
private:
    int calcNeighbours(const int x, const int y);
    void updateCell(const int height, const int width, const int neighbours);
};
