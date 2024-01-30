/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** ResourceManager
*/

#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class ResourceManager {
public:
    ResourceManager() = default;

    sf::Texture& getTexture(const std::string& filename);

private:
    std::unordered_map<std::string, sf::Texture> textures;
    sf::Texture& loadTexture(const std::string& filename);
};

#endif // RESOURCEMANAGER_HPP

