#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>

#include "LifeState.hpp"
#include "Game.hpp"

Game::Game() :
    height(128),
    width(256),
    title("Game Of Life")
{ };

void Game::run(){
    
    data->window.create(sf::VideoMode(width, height), std::string(title));
    data->assets.loadTexture("tile", "assets/tile.png");
    data->assets.loadTexture("tile2", "assets/tile2.png");
    
    auto size = data->assets.getTexture("tile").getSize();
    int width = data->window.getSize().x / size.x;
    int height = data->window.getSize().y / size.y;
    
    lifeState = LifeState(height, width, data);
    
    std::chrono::milliseconds nextGameTick{ clock.getElapsedTime().asMilliseconds() };
    
    while (data->window.isOpen()) {
        updateGame();
        displayGame();
        
        nextGameTick += skip_ticks;
        
        std::chrono::milliseconds current_time{clock.getElapsedTime().asMilliseconds()};
        std::this_thread::sleep_for(nextGameTick - current_time);
    }
}

void Game::updateGame(){
    
    lifeState.update();
    
    sf::Event event;
    while (data->window.pollEvent(event))
    {
        switch (event.type) {
            case sf::Event::Closed: {
                data->window.close();
                break;
            }
                
            case sf::Event::MouseButtonPressed: {
                auto mouse_pos = sf::Mouse::getPosition(data->window);
                sf::Vector2<float> translated_pos = data->window.mapPixelToCoords(mouse_pos);
                lifeState.toggle(translated_pos);
                break;
            }
                
            case sf::Event::KeyReleased: {
                handleKeyCode(event.key.code);
                break;
            }
                
            default:
                break;
        }
    }
}

void Game::displayGame(){
    data->window.clear(sf::Color::Black);
    lifeState.draw();
    data->window.display();
}

void Game::handleKeyCode(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Space: {
            if(lifeState.isGenerating) {
                lifeState.stop();
            } else {
                lifeState.start();
            }
            break;
        }
            
        default:
            break;
    }
}

Game& Game::setHeight(const int height) {
    this->height = height;
    return *this;
}

Game& Game::setWidth(const int width) {
    this->width = width;
    return *this;
}

Game& Game::setTitle(const std::string_view title) {
    this->title = title;
    return *this;
}
