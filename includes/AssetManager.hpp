#pragma once

#include <map>
#include <SFML/Graphics.hpp>

class AssetManager {
    
private:
    std::map<std::string, sf::Texture> textures;
    
public:
    void loadTexture (std::string name, std::string filename);
    sf::Texture *getTexture(std::string name);
    
};
