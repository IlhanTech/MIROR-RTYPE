/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** CharacterEntity
*/

#include "CharacterEntity.hpp"

CharacterEntity::CharacterEntity()
{

}

CharacterEntity::CharacterEntity(const std::string& path, float x, float y, int playerNumber) : Entity(path, x, y)
{
    sf::IntRect rect = sprite.getTextureRect();
    int indexStarShip = playerNumber - 1;
    int highStarShip = 17;


    rect.top = indexStarShip * highStarShip;
    rect.left = 0;
    rect.height = 17;
    rect.width = 32;
    sprite.setScale(2.0f, 2.0f);
    sprite.setTextureRect(rect);
}

CharacterEntity::~CharacterEntity()
{
}

sf::Sprite CharacterEntity::getSprite()
{
    return (sprite);
}

int CharacterEntity::getId()
{
    return (this->id);
}

void CharacterEntity::Update(sf::RenderWindow& window, ServerData &serverData)
{
    Entity::Update(window, serverData);
}

void animate(sf::Sprite& sprite)
{
    sf::IntRect rect = sprite.getTextureRect();

    rect.left = rect.left + 33;
    if (rect.left >= 160)
        rect.left = 0;
    rect.width = 32;
    rect.height = 17;
    sprite.setTextureRect(rect);
}

void CharacterEntity::Render(sf::RenderWindow& window, std::vector<mobData>& mobsDatas
, ServerData &serverData)
{
    //Entity::Render(window);
    window.draw(sprite);
    clocktime();
}

void CharacterEntity::clocktime()
{
    seconds = time.asMicroseconds() / 10000.0;
    time = clock.getElapsedTime();

    if (seconds > 10.5) {
        animate(sprite);
        clock.restart();
    }
}
