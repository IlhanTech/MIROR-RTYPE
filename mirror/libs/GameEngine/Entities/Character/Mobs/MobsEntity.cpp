/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** MobEntity
*/

#include "MobsEntity.hpp"
#include "../../../Server/commands.hpp"

MobsEntity::MobsEntity()
{
}

MobsEntity::MobsEntity(const std::string& imagePath, float x, float y, sf::IntRect rect
, bool boss, int id, int playerUid)
{
    std::cout << Entity::formatPath(imagePath) << std::endl;
    if (!texture.loadFromFile(Entity::formatPath(imagePath))) {
        throw std::runtime_error("Failed to load image for Entity.");
    }
    this->path = imagePath;
    verticalDirection = 1;
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    sprite.setTextureRect(rect);
    sprite.setScale(2.0f, 2.0f);
    this->id = id;
    this->playerConnectionUid = playerUid;
    this->boss= boss;
    if (boss)
        this->healthPoints = 5000;
    else if (!boss)
        this->healthPoints = 1000;
}

MobsEntity::~MobsEntity()
{
}

int MobsEntity::getId() { return (this->id); }

int MobsEntity::getPlayerConnectionUid()
{
    return (this->playerConnectionUid);
}

void MobsEntity::Update(sf::RenderWindow& window, ServerData &serverData)
{

}

void animate_mob(sf::Sprite& sprite)
{
    sf::IntRect rect = sprite.getTextureRect();

    rect.left = rect.left + (21 + 12);
    if (rect.left >= 257)
        rect.left = 5;
    rect.top = 0;
    rect.width = 21;
    rect.height = 24;
    sprite.setTextureRect(rect);
}

void animate_boss(sf::Sprite& sprite)
{
    sf::IntRect rect = sprite.getTextureRect();

    rect.left = rect.left + 65;
    if (rect.left >= 520)
        rect.left = 1;
    rect.top = 0;
    rect.width = 65;
    rect.height = 132;
    sprite.setTextureRect(rect);
}

 void MobsEntity::Render(sf::RenderWindow& window, std::vector<mobData>& mobsDatas,
 ServerData &serverData)
 {
    Entity::Render(window, mobsDatas, serverData);
    int windowHeight = window.getSize().y;
    float movementSpeed = 1.5f;

    if (boss) {
        if (sprite.getPosition().y <= 0 && verticalDirection == -1)
            verticalDirection = 1;
        else if (sprite.getPosition().y + 125 >= windowHeight - sprite.getLocalBounds().height && verticalDirection == 1)
            verticalDirection = -1;
        sprite.move(0, movementSpeed * verticalDirection);
    } else {
        // sprite.move(-movementSpeed, 0);
        commands cmds;
        cmds.sendCommand(const_cast<char *>(std::string("8 " 
        + std::to_string(this->getPlayerConnectionUid()) + " entityType:Mob entityId:" 
        + std::to_string(this->getId()) + " positionX:" 
        + std::to_string(sprite.getPosition().x - movementSpeed) + " positionY:" 
        + std::to_string(sprite.getPosition().y)).c_str()), serverData);
    }
    clocktime();
}

void MobsEntity::clocktime()
{
    seconds = time.asMicroseconds() / 10000.0;
    time = clock.getElapsedTime();

    if (seconds > 10.5) {
        if (boss)
            animate_boss(sprite);
        else if (!boss)
            animate_mob(sprite);
        clock.restart();
    }
}
