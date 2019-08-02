#include <memory>
#include <iostream>
#include "LifeState.hpp"
#include <SFML/System/Clock.hpp>

LifeState::LifeState(GameDataRef &data) {
    this->data = data;
};

void LifeState::init() {
    auto size = this->data->assets.getTexture("tile")->getSize();
    int width = this->data->window.getSize().x / size.x;
    int height = this->data->window.getSize().y / size.y;
    
    auto boolean = [](int x, int y, int height, int width) { return false; };
    
    this->currentState.fill(height, width, boolean);
    this->nextState.fill(height, width, boolean);
    
    int posX = 0;
    int posY = 0;
    sf::Texture* tile = this->data->assets.getTexture("tile");
    
    this->sprites.fill(height, width, [tile, posX, posY](int x, int y, int height, int width) mutable {
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
    
    this->lastTime = 0;
};

void LifeState::toggle(sf::Vector2<float> translated_pos) {
    
    this->sprites.forEach([&translated_pos, this](sf::Sprite sprite, int x, int y){
        if(sprite.getGlobalBounds().contains(translated_pos)) {
            if(this->currentState.get(x, y)) {
                this->currentState.set(x, y, false);
            } else {
                this->currentState.set(x, y, true);
            }
        }
    });
}

void LifeState::draw() {
    
    sf::Texture* tile = this->data->assets.getTexture("tile");
    sf::Texture* tile2 = this->data->assets.getTexture("tile2");
    
    sprites.forEach([this, tile, tile2](sf::Sprite sprite, int x, int y){
        if(this->currentState.get(x, y)) {
            sprite.setTexture(*tile2);
        } else {
            sprite.setTexture(*tile);
        }
        this->data->window.draw(sprite);
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
        double time_counter = 0;
        
        int thisTime = clock.getElapsedTime().asSeconds();
        
        time_counter += (double)(thisTime - this->lastTime);
        
        if(time_counter > 0)
        {
            currentState.forEach([this](bool value, int x, int y) {
                const int neighbours = this->getNeighbours(x, y);
                this->updateCell(x, y, neighbours);
            });
            
            this->currentState = nextState;
        }
        this->lastTime = thisTime;
    }
}

int LifeState::getNeighbours(const int i, const int j) {
    int neighbours = 0;
    
    if(i == this->currentState.sizeX()-1 && j == currentState.sizeY(i)-1) {
        if(this->currentState.get(i-1, j)) {
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
    
    if(i == this->currentState.sizeX()-1 && j > 0) {
        
        if(this->currentState.get(i, j-1)) {
            neighbours++;
        }
        
        if(this->currentState.get(i-1, j-1)) {
            neighbours++;
        }
        
        if(this->currentState.get(i-1, j)) {
            neighbours++;
        }
        
        if(this->currentState.get(i-1, j+1)) {
            neighbours++;
        }
        
        if(this->currentState.get(i, j+1)) {
            neighbours++;
        }
        return neighbours;
    }
    
    if(i == this->currentState.sizeX()-1 && j == 0) {
        if(this->currentState.get(i-1, j)) {
            neighbours++;
        }
        
        if(this->currentState.get(i-1, j+1)) {
            neighbours++;
        }
        
        if(this->currentState.get(i, j+1)) {
            neighbours++;
        }
        return neighbours;
    }
    
    if(i == 0 && j == 0) {
        if(this->currentState.get(i, j+1)) {
            neighbours++;
        }
        
        if(this->currentState.get(i+1, j+1)) {
            neighbours++;
        }
        
        if(this->currentState.get(i+1, j)) {
            neighbours++;
        }
        return neighbours;
    }
    
    if(i == 0 && j == this->currentState.sizeY(i)-1) {
        if(this->currentState.get(i, j-1)) {
            neighbours++;
        }
        
        if(this->currentState.get(i+1, j-1)) {
            neighbours++;
        }
        
        if(this->currentState.get(i+1, j)) {
            neighbours++;
        }
        return neighbours;
    }
    
    if(i == 0 && j > 0) {
        if(this->currentState.get(i, j+1)) {
            neighbours++;
        }
        
        if(this->currentState.get(i+1, j+1)) {
            neighbours++;
        }
        
        if(this->currentState.get(i+1, j)) {
            neighbours++;
        }
        
        if(this->currentState.get(i+1, j-1)) {
            neighbours++;
        }
        
        if(this->currentState.get(i, j-1)) {
            neighbours++;
        }
        return neighbours;
    }
    
    if(i > 0 && j == 0) {
        if(this->currentState.get(i-1, j)) {
            neighbours++;
        }
        
        if(this->currentState.get(i-1, j+1)) {
            neighbours++;
        }
        
        if(this->currentState.get(i, j+1)) {
            neighbours++;
        }
        
        if(this->currentState.get(i+1, j+1)) {
            neighbours++;
        }
        
        if(this->currentState.get(i+1, j)) {
            neighbours++;
        }
        return neighbours;
    }
    
    if(i > 0 && j == this->currentState.sizeY(i)-1) {
        if(this->currentState.get(i-1, j-1)) {
            neighbours++;
        }
        
        if(this->currentState.get(i-1, j)) {
            neighbours++;
        }
        
        if(this->currentState.get(i, j-1)) {
            neighbours++;
        }
        
        if(this->currentState.get(i+1, j-1)) {
            neighbours++;
        }
        
        if(this->currentState.get(i+1, j)) {
            neighbours++;
        }
        return neighbours;
    }
    
    if(i > 0 && j > 0) {
        if(this->currentState.get(i-1, j)) {
            neighbours++;
        }
        
        if(this->currentState.get(i-1, j+1)) {
            neighbours++;
        }
        
        if(this->currentState.get(i, j+1)) {
            neighbours++;
        }
        
        if(this->currentState.get(i+1, j+1)) {
            neighbours++;
        }
        
        if(this->currentState.get(i+1, j)) {
            neighbours++;
        }
        if(this->currentState.get(i+1, j-1)) {
            neighbours++;
        }
        if(this->currentState.get(i, j-1)) {
            neighbours++;
        }
        if(this->currentState.get(i-1, j-1)) {
            neighbours++;
        }
        return neighbours;
    }
    return neighbours;
}

void LifeState::updateCell(const int height, const int width, const int neighbours) {
    
    const bool isActive = this->currentState.get(height, width);
    
    if(neighbours < 2 && isActive) {
        this->nextState.set(height, width, false);
        return;
    } else if((neighbours == 2 || neighbours == 3) && isActive) {
        this->nextState.set(height, width, true);
        return;
    } else if(neighbours > 3 && isActive) {
       this->nextState.set(height, width, false);
        return;
    } else if(isActive == false && neighbours == 3) {
        this->nextState.set(height, width, true);
        return;
    }
}
