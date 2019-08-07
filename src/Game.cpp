#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>

#include "LifeState.hpp"
#include "Game.hpp"

Game::Game(OpenGame& params) :
    cellHeight(params.cellHeight_),
    cellWidth(params.cellWidth_),
    title(params.title_),
    lifeState(params.cellHeight_, params.cellWidth_, data)
{ };

void Game::run()
{
    auto tileSize = data->assets.getTexture("tile").getSize();
    unsigned int windowHeight = tileSize.y * cellHeight;
    unsigned int windowWidth = tileSize.x * cellWidth;
    
    data->window.create(sf::VideoMode(windowWidth, windowHeight), std::string(title));
    std::chrono::milliseconds nextGameTick{ clock.getElapsedTime().asMilliseconds() };
    
    while (data->window.isOpen()) {
        updateGame();
        displayGame();
        
        nextGameTick += skip_ticks;
        
        std::chrono::milliseconds current_time{clock.getElapsedTime().asMilliseconds()};
        std::this_thread::sleep_for(nextGameTick - current_time);
    }
}

void Game::updateGame()
{
    
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

void Game::displayGame()
{
    data->window.clear(sf::Color::Black);
    lifeState.draw();
    data->window.display();
}

void Game::handleKeyCode(sf::Keyboard::Key key)
{
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
