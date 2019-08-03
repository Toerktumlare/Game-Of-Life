#include <memory>
#include <iostream>
#include "LifeState.hpp"
#include <SFML/System/Clock.hpp>
#include <chrono>

LifeState::LifeState(GameDataRef &data) {
    this->data = data;
};

void LifeState::init() {
    auto size = data->assets.getTexture("tile")->getSize();
    int width = data->window.getSize().x / size.x;
    int height = data->window.getSize().y / size.y;
    
    auto boolean = [](int x, int y, int height, int width) { return false; };
    
    currentState.fill(height, width, boolean);
    nextState.fill(height, width, boolean);
    
    int posX = 0;
    int posY = 0;
    sf::Texture* tile = data->assets.getTexture("tile");
    
    sprites.fill(height, width, [tile, posX, posY](int x, int y, int height, int width) mutable {
        sf::Sprite sprite;
        sprite.setTexture(*tile);
        sprite.setTextureRect(sf::IntRect(0, 0, tile->getSize().x, tile->getSize().y));
        sprite.setPosition(posX, posY);
        posX += tile->getSize().x;
        
        if(y == width-1) {
            posY += tile->getSize().y;
            posX = 0;
        }
        
        return sprite;
    });
};

void LifeState::toggle(sf::Vector2<float> translated_pos) {
    
    sprites.forEach([&translated_pos, this](sf::Sprite sprite, int x, int y){
        if(sprite.getGlobalBounds().contains(translated_pos)) {
            if(currentState.get(x, y)) {
                currentState.set(x, y, false);
            } else {
                currentState.set(x, y, true);
            }
        }
    });
}

void LifeState::draw() {
    
    sf::Texture* tile = data->assets.getTexture("tile");
    sf::Texture* tile2 = data->assets.getTexture("tile2");
    
    sprites.forEach([this, tile, tile2](sf::Sprite sprite, int x, int y){
        if(currentState.get(x, y)) {
            sprite.setTexture(*tile2);
        } else {
            sprite.setTexture(*tile);
        }
        data->window.draw(sprite);
    });
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
            currentState.forEach([this](bool value, int x, int y) {
                const int neighbours = this->getNeighbours(x, y);
                updateCell(x, y, neighbours);
            });
            
            currentState = nextState;
            acc_delta = std::chrono::milliseconds{0};
        }
        lastTime = nowTime;
    }
}

int LifeState::getNeighbours(const int i, const int j) {
    int neighbours = 0;
    
    if(i == currentState.sizeX()-1 && j == currentState.sizeY(i)-1) {
        if(currentState.get(i-1, j)) {
            neighbours++;
        }
        
        if(currentState.get(i-1, j-1)) {
            neighbours++;
        }
        
        if(currentState.get(i, j-1)) {
            neighbours++;
        }
        return neighbours;
    }
    
    if(i == currentState.sizeX()-1 && j > 0) {
        
        if(currentState.get(i, j-1)) {
            neighbours++;
        }
        
        if(currentState.get(i-1, j-1)) {
            neighbours++;
        }
        
        if(currentState.get(i-1, j)) {
            neighbours++;
        }
        
        if(currentState.get(i-1, j+1)) {
            neighbours++;
        }
        
        if(currentState.get(i, j+1)) {
            neighbours++;
        }
        return neighbours;
    }
    
    if(i == currentState.sizeX()-1 && j == 0) {
        if(currentState.get(i-1, j)) {
            neighbours++;
        }
        
        if(currentState.get(i-1, j+1)) {
            neighbours++;
        }
        
        if(currentState.get(i, j+1)) {
            neighbours++;
        }
        return neighbours;
    }
    
    if(i == 0 && j == 0) {
        if(currentState.get(i, j+1)) {
            neighbours++;
        }
        
        if(currentState.get(i+1, j+1)) {
            neighbours++;
        }
        
        if(currentState.get(i+1, j)) {
            neighbours++;
        }
        return neighbours;
    }
    
    if(i == 0 && j == currentState.sizeY(i)-1) {
        if(currentState.get(i, j-1)) {
            neighbours++;
        }
        
        if(currentState.get(i+1, j-1)) {
            neighbours++;
        }
        
        if(currentState.get(i+1, j)) {
            neighbours++;
        }
        return neighbours;
    }
    
    if(i == 0 && j > 0) {
        if(currentState.get(i, j+1)) {
            neighbours++;
        }
        
        if(currentState.get(i+1, j+1)) {
            neighbours++;
        }
        
        if(currentState.get(i+1, j)) {
            neighbours++;
        }
        
        if(currentState.get(i+1, j-1)) {
            neighbours++;
        }
        
        if(currentState.get(i, j-1)) {
            neighbours++;
        }
        return neighbours;
    }
    
    if(i > 0 && j == 0) {
        if(currentState.get(i-1, j)) {
            neighbours++;
        }
        
        if(currentState.get(i-1, j+1)) {
            neighbours++;
        }
        
        if(currentState.get(i, j+1)) {
            neighbours++;
        }
        
        if(currentState.get(i+1, j+1)) {
            neighbours++;
        }
        
        if(currentState.get(i+1, j)) {
            neighbours++;
        }
        return neighbours;
    }
    
    if(i > 0 && j == currentState.sizeY(i)-1) {
        if(currentState.get(i-1, j-1)) {
            neighbours++;
        }
        
        if(currentState.get(i-1, j)) {
            neighbours++;
        }
        
        if(currentState.get(i, j-1)) {
            neighbours++;
        }
        
        if(currentState.get(i+1, j-1)) {
            neighbours++;
        }
        
        if(currentState.get(i+1, j)) {
            neighbours++;
        }
        return neighbours;
    }
    
    if(i > 0 && j > 0) {
        if(currentState.get(i-1, j)) {
            neighbours++;
        }
        
        if(currentState.get(i-1, j+1)) {
            neighbours++;
        }
        
        if(currentState.get(i, j+1)) {
            neighbours++;
        }
        
        if(currentState.get(i+1, j+1)) {
            neighbours++;
        }
        
        if(currentState.get(i+1, j)) {
            neighbours++;
        }
        if(currentState.get(i+1, j-1)) {
            neighbours++;
        }
        if(currentState.get(i, j-1)) {
            neighbours++;
        }
        if(currentState.get(i-1, j-1)) {
            neighbours++;
        }
        return neighbours;
    }
    return neighbours;
}

void LifeState::updateCell(const int height, const int width, const int neighbours) {
    
    const bool isActive = currentState.get(height, width);
    
    if(neighbours < 2 && isActive) {
        nextState.set(height, width, false);
        return;
    } else if((neighbours == 2 || neighbours == 3) && isActive) {
        nextState.set(height, width, true);
        return;
    } else if(neighbours > 3 && isActive) {
       nextState.set(height, width, false);
        return;
    } else if(isActive == false && neighbours == 3) {
        nextState.set(height, width, true);
        return;
    }
}
