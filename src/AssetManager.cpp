#include "AssetManager.hpp"

void AssetManager::loadTexture(std::string name, std::string filename) {
    sf::Texture texture;
    
    if(texture.loadFromFile(filename)) {
        this->textures[name] = texture;
    }
}

sf::Texture *AssetManager::getTexture(std::string name) {
    return &this->textures.at(name);
}
