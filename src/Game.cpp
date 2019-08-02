#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>

#include "LifeState.hpp"
#include "Game.hpp"

const int Game::FPS = 25;
const int Game::SKIP_TICKS = 1000 / FPS;

Game::Game() :
    height(128), width(128), title("Game Of Life"), lifeState(this->data)
{ };

void Game::run(){
    
    data->window.create(sf::VideoMode(width, height), std::string(title));
    data->assets.loadTexture("tile", "assets/tile.png");
    data->assets.loadTexture("tile2", "assets/tile2.png");
    lifeState.init();
    
    int nextGameTick = clock.getElapsedTime().asMilliseconds();
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 0;
    
    while (data->window.isOpen()) {
        updateGame();
        displayGame();
        
        nextGameTick += SKIP_TICKS;
        
        tim.tv_nsec = (nextGameTick - clock.getElapsedTime().asMilliseconds());
        
        if(tim.tv_nsec >= 0){
            nanosleep(&tim, &tim2);
        }
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
                sf::Vector2<float> translated_pos = this->data->window.mapPixelToCoords(mouse_pos);
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
