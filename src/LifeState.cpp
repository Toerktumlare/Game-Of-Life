#include <memory>
#include <iostream>
#include "LifeState.hpp"
#include <SFML/System/Clock.hpp>


void LifeState::init(GameDataRef &data) {
    this->data = data;
    auto size = this->data->assets.getTexture("tile")->getSize();
    int width = this->data->window.getSize().x / size.x;
    int height = this->data->window.getSize().y / size.y;
    
    currentState.reserve(width);
    
    for (int i = 0; i < height; i++) {
        std::vector<bool> v;
        v.reserve(width);
        currentState.push_back(v);
        for (int j = 0; j < width; j++) {
            this->currentState.at(i).push_back(false);
        }
    }
    
    nextState.reserve(width);
    
    for (int i = 0; i < height; i++) {
        std::vector<bool> v;
        v.reserve(width);
        nextState.push_back(v);
        for (int j = 0; j < width; j++) {
            this->nextState.at(i).push_back(false);
        }
    }
    
    sf::Texture* tile = this->data->assets.getTexture("tile");
    
    int posX = 0;
    int posY = 0;
    
    sprites.reserve(height);
    
    for (int i = 0; i < currentState.size(); i++) {
        std::vector<sf::Sprite> v;
        v.reserve(width);
        sprites.push_back(v);
        for (int j = 0; j < currentState.at(i).size(); j++) {
            
            sf::Sprite sprite;
            sprite.setTexture(*tile);
            sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
            sprite.setPosition(posX, posY);
            sprites.at(i).push_back(sprite);
            posX += tile->getSize().x;
            
        }
        posY += tile->getSize().y;
        posX = 0;
    }
    
    this->lastTime = 0;
};

void LifeState::toggle(sf::Vector2<float> translated_pos) {
    
    for (int i = 0; i < sprites.size(); i++) {
        for (int j = 0; j < sprites.at(i).size(); j++) {
            if(sprites.at(i).at(j).getGlobalBounds().contains(translated_pos)) {
                if(currentState.at(i).at(j)) {
                    currentState.at(i).at(j) = false;
                    return;
                } else {
                    currentState.at(i).at(j) = true;
                    return;
                }
            }
        }
    }
}

void LifeState::draw() {
    
    sf::Texture* tile = this->data->assets.getTexture("tile");
    sf::Texture* tile2 = this->data->assets.getTexture("tile2");
    
    for (int i = 0; i < sprites.size(); i++) {
        for (int j = 0; j < sprites.at(i).size(); j++) {
            if(currentState.at(i).at(j)) {
                sprites.at(i).at(j).setTexture(*tile2);
            } else {
               sprites.at(i).at(j).setTexture(*tile);
            }
            this->data->window.draw(sprites.at(i).at(j));
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
        double time_counter = 0;
        
        int thisTime = clock.getElapsedTime().asSeconds();
        
        time_counter += (double)(thisTime - this->lastTime);
        
        if(time_counter > 0)
        {
            for (int i = 0; i < currentState.size(); i++) {
                for (int j = 0; j < currentState.at(i).size(); j++) {
                    int neighbours = 0;
                    
                    if(i == currentState.size()-1 && j == currentState.at(i).size()-1) {
                        if(currentState.at(i-1).at(j)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i-1).at(j-1)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i).at(j-1)) {
                            neighbours++;
                        }
                        updateCell(i, j, neighbours);
                        continue;
                    }
                    
                    if(i == currentState.size()-1 && j > 0) {
                        
                        if(currentState.at(i).at(j-1)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i-1).at(j-1)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i-1).at(j)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i-1).at(j+1)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i).at(j+1)) {
                            neighbours++;
                        }
                        updateCell(i, j, neighbours);
                        continue;
                    }
                    
                    if(i == currentState.size()-1 && j == 0) {
                        if(currentState.at(i-1).at(j)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i-1).at(j+1)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i).at(j+1)) {
                            neighbours++;
                        }
                        updateCell(i, j, neighbours);
                        continue;
                    }
                    
                    if(i == 0 && j == 0) {
                        if(currentState.at(i).at(j+1)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i+1).at(j+1)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i+1).at(j)) {
                            neighbours++;
                        }
                        updateCell(i, j, neighbours);
                        continue;
                    }
                    
                    if(i == 0 && j == currentState.at(i).size()-1) {
                        if(currentState.at(i).at(j-1)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i+1).at(j-1)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i+1).at(j)) {
                            neighbours++;
                        }
                        updateCell(i, j, neighbours);
                        continue;
                    }
                    
                    if(i == 0 && j > 0) {
                        if(currentState.at(i).at(j+1)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i+1).at(j+1)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i+1).at(j)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i+1).at(j-1)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i).at(j-1)) {
                            neighbours++;
                        }
                        updateCell(i, j, neighbours);
                        continue;
                    }
                    
                    if(i > 0 && j == 0) {
                        if(currentState.at(i-1).at(j)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i-1).at(j+1)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i).at(j+1)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i+1).at(j+1)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i+1).at(j)) {
                            neighbours++;
                        }
                        updateCell(i, j, neighbours);
                        continue;
                    }
                    
                    if(i > 0 && j == currentState.at(i).size()-1) {
                        if(currentState.at(i-1).at(j-1)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i-1).at(j)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i).at(j-1)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i+1).at(j-1)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i+1).at(j)) {
                            neighbours++;
                        }
                        updateCell(i, j, neighbours);
                        continue;
                    }

                    if(i > 0 && j > 0) {
                        if(currentState.at(i-1).at(j)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i-1).at(j+1)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i).at(j+1)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i+1).at(j+1)) {
                            neighbours++;
                        }
                        
                        if(currentState.at(i+1).at(j)) {
                            neighbours++;
                        }
                        if(currentState.at(i+1).at(j-1)) {
                            neighbours++;
                        }
                        if(currentState.at(i).at(j-1)) {
                            neighbours++;
                        }
                        if(currentState.at(i-1).at(j-1)) {
                            neighbours++;
                        }
                        updateCell(i, j, neighbours);
                        continue;
                    }
                    updateCell(i, j, neighbours);
                }
            }
            
            this->currentState = nextState;
        }
        
        this->lastTime = thisTime;
    }
}

void LifeState::updateCell(const int height, const int width, const int neighbours) {
    
    const bool isActive = currentState.at(height).at(width);
    
    if(neighbours < 2 && isActive) {
        nextState.at(height).at(width) = false;
        return;
    } else if((neighbours == 2 || neighbours == 3) && isActive) {
        nextState.at(height).at(width) = true;
        return;
    } else if(neighbours > 3 && isActive) {
        nextState.at(height).at(width) = false;
        return;
    } else if(isActive == false && neighbours == 3) {
        nextState.at(height).at(width) = true;
        return;
    }
}
