#include <memory>
#include <iostream>
#include "LifeState.hpp"
#include <SFML/System/Clock.hpp>
#include <chrono>

LifeState::LifeState(size_t height, size_t width, GameDataRef &data) : isGenerating(false)
{
    this->data = data;
    data->assets.loadTexture("tile", "assets/tile.png");
    data->assets.loadTexture("tile2", "assets/tile2.png");
    
    currentState.reserve(height+2);
    for (int i = 0; i < height+2; ++i) {
        std::vector<bool> row;
        row.reserve(width+2);
        currentState.push_back(row);
        for (int j = 0; j < width+2; ++j) {
            currentState[i].push_back(false);
        }
    }
    
    nextState = currentState;
    
    auto tile = data->assets.getTexture("tile");
    
    int posX = 0;
    int posY = 0;
    
    for (int i = 0; i < height; ++i) {
        std::vector<sf::Sprite> row;
        row.reserve(width);
        sprites.push_back(row);
        for (int j = 0; j < width; ++j) {
            
            sf::Sprite sprite;
            sprite.setTexture(tile);
            sprite.setTextureRect(sf::IntRect(0, 0, tile.getSize().x, tile.getSize().y));
            sprite.setPosition(posX, posY);
            posX += tile.getSize().x;
            
            if(j == width-1) {
                posY += tile.getSize().y;
                posX = 0;
            }
            
            sprites[i].push_back(sprite);
        }
    }
};

void LifeState::toggle(sf::Vector2<float> translated_pos) {
    
    for (int i = 0; i < sprites.size(); ++i) {
        for (int j = 0; j < sprites[i].size(); ++j) {
            if(sprites[i][j].getGlobalBounds().contains(translated_pos)) {
                if(currentState[i+1][j+1]) {
                    currentState[i+1][j+1] = false;
                } else {
                    currentState[i+1][j+1] = true;
                }
            }
        }
    }
}

void LifeState::draw() {
    
    sf::Texture tile = data->assets.getTexture("tile");
    sf::Texture tile2 = data->assets.getTexture("tile2");
    
    for (int i = 0; i < sprites.size(); ++i) {
        for (int j = 0; j < sprites[i].size(); ++j) {
            if(currentState[i+1][j+1]) {
                sprites[i][j].setTexture(tile2);
            } else {
                sprites[i][j].setTexture(tile);
            }
            data->window.draw(sprites[i][j]);
        }
    }
}

void LifeState::start() {
    std::cout << "Started simulation" << std::endl;
    isGenerating = true;
}

void LifeState::stop() {
    std::cout << "Stopped simulation" << std::endl;
    isGenerating = false;
}

void LifeState::update() {
    
    if(isGenerating) {
        
        std::chrono::milliseconds nowTime{ clock.getElapsedTime().asMilliseconds() };
        
        acc_delta += nowTime - lastTime;
        if(acc_delta > std::chrono::milliseconds{30})
        {
            for (int i = 1; i < currentState.size()-1; ++i) {
                for (int j = 1; j < currentState[j].size()-1; ++j) {
                    
                    int neighbours = calcNeighbours(i, j);
                    updateCell(i, j, neighbours);
                }
            }
            currentState = nextState;
            acc_delta = std::chrono::milliseconds{0};
        }
        lastTime = nowTime;
    }
}

int LifeState::calcNeighbours(const int i, const int j) {
    int neighbours = 0;
    for (int k = i-1; k < i + 2; ++k) {
        for (int l = j-1; l < j + 2; ++l) {
            if(currentState[k][l]) {
                ++neighbours;
            }
        }
    }
    if(currentState[i][j]) {
        --neighbours;
    }
    
    return neighbours;
};

void LifeState::updateCell(const int height, const int width, const int neighbours) {
    
    const bool isActive = currentState[height][width];
    
    if(neighbours < 2 && isActive) {
        nextState[height][width] = false;
        return;
    } else if((neighbours == 2 || neighbours == 3) && isActive) {
        nextState[height][width] = true;
        return;
    } else if(neighbours > 3 && isActive) {
        nextState[height][width] = false;
        return;
    } else if(isActive == false && neighbours == 3) {
        nextState[height][width] = true;
        return;
    }
}
