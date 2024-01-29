/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville [WSL: Ubuntu]
** File description:
** MissileEntity
*/

#include "MissileEntity.hpp"
#include "../Player/PlayerEntity.hpp"
#include "../../../Server/commands.hpp"

MissileEntity::MissileEntity()
{
}

MissileEntity::MissileEntity(float x, float y, MissileEntity::DIRECTION direction
, int id, int playerUid)
{
    std::string imagePath = "assets/sprites/r-typesheet1.gif";

    if (!texture.loadFromFile(Entity::formatPath(imagePath))) {
        throw std::runtime_error("Failed to load image for Entity.");
    }

    sf::IntRect rect = sprite.getTextureRect();

    rect.top = 80;
    rect.left = 247;
    rect.width = 18;
    rect.height = 20;

    sprite.setTextureRect(rect);
    sprite.setTexture(texture);
    sprite.setPosition(x + 70, y + 10);

    this->direction = direction;
    this->missileDamage = 75;
    this->targetReached = false;
    this->id = id;
    this->playerUid = playerUid;
}

MissileEntity::~MissileEntity()
{
}

void MissileEntity::Update(sf::RenderWindow& window, ServerData &serverData)
{
    CharacterEntity::Update(window, serverData);
}

void MissileEntity::setReachTarget(bool b) { this->targetReached = b; }

bool MissileEntity::hasReachedTarget() { return (this->targetReached); }

sf::Vector2f MissileEntity::getSpritePosition()
{
    return (sprite.getPosition());
}

int MissileEntity::getId()
{
    return (this->id);
}

int MissileEntity::getPlayerUid()
{
    return (this->playerUid);
}

void MissileEntity::Render(sf::RenderWindow& window, std::vector<mobData>& mobsDatas
, ServerData &serverData)
{
    window.draw(sprite);

    float movementSpeed = 7.5f;

    if (direction == WEST) {
        sprite.move(-movementSpeed, 0);
    }
    if (direction == EAST) {
        // sprite.move(movementSpeed, 0);
        commands cmds;
        cmds.sendCommand(const_cast<char *>(std::string("8 " 
        + std::to_string(this->getPlayerUid()) + " entityType:Missile entityId:" 
        + std::to_string(this->getId()) + " positionX:" 
        + std::to_string(sprite.getPosition().x + movementSpeed) + " positionY:" 
        + std::to_string(sprite.getPosition().y)).c_str()), serverData);
    }
    check_colliding(mobsDatas);
}

void MissileEntity::check_colliding(std::vector<mobData>& mobsDatas)
{
    int i = 0;
    for (auto& mob : mobsDatas) {
        sf::Vector2f pos = mob.sprite.getPosition();
        if (isColliding(mob.sprite) == true) {
            int current_hp = mob.healthPoints;
            mob.healthPoints = (current_hp -= this->missileDamage);
            this->setReachTarget(true);
        }
    }
}

bool MissileEntity::isColliding(sf::Sprite c_sprite)
{
    sf::FloatRect missileBounds = sprite.getGlobalBounds();
    sf::FloatRect missileBounds_c = c_sprite.getGlobalBounds();

    if (missileBounds.intersects(missileBounds_c))
        return (true);
    return (false);
}
