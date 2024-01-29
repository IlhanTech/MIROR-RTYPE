/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** ResourceManager
*/

#include "ResourceManager.hpp"
#include <stdexcept>

sf::Texture& ResourceManager::getTexture(const std::string& filename)
{
    auto it = textures.find(filename);
    if (it != textures.end()) {
        return it->second;
    } else {
        return loadTexture(filename);
    }
}

sf::Texture& ResourceManager::loadTexture(const std::string& filename)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        throw std::runtime_error("Failed to load texture: " + filename);
    }

    auto inserted = textures.emplace(filename, std::move(texture));
    return inserted.first->second;
}
