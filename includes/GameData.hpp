#pragma once

#include <memory>
#include <stack>
#include "AssetManager.hpp"
#include "LifeState.hpp"

struct GameData {
    AssetManager assets;
    sf::RenderWindow window;
};

typedef std::shared_ptr<GameData> GameDataRef;
