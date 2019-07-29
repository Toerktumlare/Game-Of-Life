#pragma once

#include <memory>
#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "LifeState.hpp"

struct GameData {
    AssetManager assets;
    InputManager input;
    sf::RenderWindow window;
};

typedef std::shared_ptr<GameData> GameDataRef;
