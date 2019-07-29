#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>

#include "LifeState.hpp"
#include "Game.hpp"

const int Game::FPS = 25;
const int Game::SKIP_TICKS = 1000 / FPS;

Game::Game(const int width, const int height, const std::string title) {
    this->data->window.create(sf::VideoMode(width, height), title);
    this->data->assets.loadTexture("tile", "assets/tile.png");
    this->data->assets.loadTexture("tile2", "assets/tile2.png");
    this->lifeState.init(this->data);
};

void Game::run(){
    
    int nextGameTick = clock.getElapsedTime().asMilliseconds();
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 0;
    
    while (this->data->window.isOpen()) {
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
    
    this->lifeState.update();
    
    sf::Event event;
    while (this->data->window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            this->data->window.close();
        }
        
        if(event.type == sf::Event::MouseButtonPressed) {
            auto mouse_pos = sf::Mouse::getPosition(this->data->window);
            sf::Vector2<float> translated_pos = this->data->window.mapPixelToCoords(mouse_pos);
            this->lifeState.toggle(translated_pos);
                        
            std::cout << "mouse clicked at: " << event.mouseButton.x << " " << event.mouseButton.y << std::endl;
        }
        
        if(event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Space) {
                if(lifeState.isGenerating) {
                    this->lifeState.stop();
                } else {
                    this->lifeState.start();
                }
            }
        }
    }
}

void Game::displayGame(){
    this->data->window.clear(sf::Color::Black);
    this->lifeState.draw();
    this->data->window.display();
}
