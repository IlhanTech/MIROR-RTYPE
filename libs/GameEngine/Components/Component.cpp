/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** Component
*/

#include "Component.hpp"

Component::Component(const std::string name, const std::string& imagePath, const sf::Vector2f& size) : name(name), path(imagePath)
{
    if (!texture.loadFromFile(Component::formatPath(imagePath))) {
        throw std::runtime_error("Failed to load image for Component.");
    }
    sprite.setTexture(texture);
    sprite.setScale(size.x / sprite.getLocalBounds().width, size.y / sprite.getLocalBounds().height);
}

Component::~Component()
{

}

void Component::Update()
{

}

void Component::Render(sf::RenderWindow& window)
{
    window.draw(sprite);
}

std::string Component::getName() const
{
    return name;
}

std::string Component::formatPath(const std::string& path)
{
    std::filesystem::path currentPath = std::filesystem::current_path();

    if (currentPath.string().find("client") != std::string::npos) {
        currentPath = currentPath.parent_path();
    }

    std::filesystem::path fullPath = currentPath / path;
    return fullPath.string();
}
