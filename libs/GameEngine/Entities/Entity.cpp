/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** Entity
*/

#include "Entity.hpp"

Entity::Entity()
{
}

Entity::Entity(const std::string& imagePath, float posX, float posY) : path(imagePath)
{
    std::cout << Entity::formatPath(imagePath) << std::endl;
    if (!texture.loadFromFile(Entity::formatPath(imagePath))) {
        throw std::runtime_error("Failed to load image for Entity.");
    }
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);
}

Entity::Entity(const std::string& imagePath, float posX, float posY
, sf::IntRect rect, const sf::Vector2f& size) : path(imagePath)
{
    std::cout << Entity::formatPath(imagePath) << std::endl;
    if (!texture.loadFromFile(Entity::formatPath(imagePath))) {
        throw std::runtime_error("Failed to load image for Entity.");
    }

    texture.setRepeated(true);
    sprite.setTextureRect(rect);
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);
    sprite.setScale(size.x / sprite.getLocalBounds().width, size.y / sprite.getLocalBounds().height);
}

Entity::~Entity()
{
}

void Entity::setHealthPoint(int healthPoints)
{
    this->healthPoints = healthPoints;
}

int Entity::getHealthPoint()
{
    return (this->healthPoints);
}

void Entity::Update(sf::RenderWindow& window, ServerData &serverData)
{

}

void Entity::Render(sf::RenderWindow& window, std::vector<mobData>& mobsDatas
, ServerData &serverData)
{
    window.draw(sprite);

    //clock_parallax();
}

sf::Sprite Entity::getSprite()
{
    return (this->sprite);
}

void Entity::setSpriteRect(sf::IntRect rect)
{
    this->sprite.setTextureRect(rect);
}

std::string Entity::getName() const
{
    return (path);
}

std::string Entity::formatPath(const std::string& path)
{
    std::filesystem::path currentPath = std::filesystem::current_path();

    if (currentPath.string().find("client") != std::string::npos) {
        currentPath = currentPath.parent_path();
    }

    std::filesystem::path fullPath = currentPath / path;
    return fullPath.string();
}

Entity::pos Entity::getPos() const
{
    Entity::pos position;
    position.x = sprite.getPosition().x;
    position.y = sprite.getPosition().y;
    return (position);
}

void Entity::setPos(pos position)
{
    this->position = position;
    this->sprite.setPosition(position.x, position.y);
}
