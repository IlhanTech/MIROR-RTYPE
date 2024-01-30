/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** PlayerEntity
*/

#include "../../../Server/commands.hpp"
#include "PlayerEntity.hpp"

PlayerEntity::PlayerEntity()
{
}

PlayerEntity::PlayerEntity(const std::string& path, float x, float y, int playerNumber, int uid) : CharacterEntity(path, x, y, playerNumber)
{
    this->uid = uid;
}

PlayerEntity::~PlayerEntity()
{
}

int PlayerEntity::getUid()
{
    return (this->uid);
}

int PlayerEntity::getId()
{
    return (this->uid);
}

void PlayerEntity::setUid(int uid)
{
    this->uid = uid;
}

void PlayerEntity::addMissile(std::unique_ptr<MissileEntity> missileEntity)
{
    missiles.push_back(std::move(missileEntity));
}

std::vector<std::unique_ptr<MissileEntity>>& PlayerEntity::getMissiles()
{
    return (this->missiles);
}

int PlayerEntity::getMissileSize()
{
    return (this->missiles.size());
}

void PlayerEntity::Update(sf::RenderWindow& window, ServerData &serverData)
{
    sf::Vector2u windowSize = window.getSize();
    unsigned int windowWidth = windowSize.x;
    unsigned int windowHeight = windowSize.y;
    float movementSpeed = 5.0f;

    if (window.hasFocus()) {
        // Key pressed Left
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (!(sprite.getPosition().x <= 20)) {
                // sprite.move(-movementSpeed, 0);
                // sprite.setPosition(this->getPos().x - movementSpeed
                // , this->getPos().y);

                commands cmds;
                cmds.sendCommand(const_cast<char *>(std::string("8 " 
                + std::to_string(this->getUid()) + " entityType:Player" + " entityId:" 
                + std::to_string(this->getUid()) + " positionX:" 
                + std::to_string(sprite.getPosition().x - movementSpeed) + " positionY:" 
                + std::to_string(sprite.getPosition().y)).c_str()), serverData);
                std::cout << "client-side: " << std::to_string(this->getUid()) 
                << "\n";
            }
        }
        // Key pressed Right
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (!(sprite.getPosition().x >= (windowWidth / 2) - 10)) {
                // sprite.move(movementSpeed, 0);
                // sprite.setPosition(this->getPos().x + movementSpeed
                // , this->getPos().y);

                commands cmds;
                cmds.sendCommand(const_cast<char *>(std::string("8 " 
                + std::to_string(this->getUid()) + " entityType:Player" + " entityId:" 
                + std::to_string(this->getUid()) + " positionX:" 
                + std::to_string(sprite.getPosition().x + movementSpeed) + " positionY:" 
                + std::to_string(sprite.getPosition().y)).c_str()), serverData);
                std::cout << "client-side: " << std::to_string(this->getUid()) 
                << "\n";
            }
        }
        // Key pressed Up
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (!(sprite.getPosition().y <= 10)) {
                // sprite.move(0, -movementSpeed);
                // sprite.setPosition(this->getPos().x, this->getPos().y - movementSpeed);

                commands cmds;
                cmds.sendCommand(const_cast<char *>(std::string("8 " 
                + std::to_string(this->getUid()) + " entityType:Player" + " entityId:" 
                + std::to_string(this->getUid()) + " positionX:"  
                + std::to_string(sprite.getPosition().x) + " positionY:" 
                + std::to_string(sprite.getPosition().y - movementSpeed)).c_str()), serverData);
                std::cout << "client-side: " << std::to_string(this->getUid()) 
                << "\n";
            }
        }
        // Key pressed Down
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (!(sprite.getPosition().y >= windowHeight - 50)) {
                // sprite.move(0, movementSpeed);
                // sprite.setPosition(this->getPos().x
                // , this->getPos().y + movementSpeed);

                commands cmds;
                cmds.sendCommand(const_cast<char *>(std::string("8 " 
                + std::to_string(this->getUid()) + " entityType:Player" + " entityId:" 
                + std::to_string(this->getUid()) + " positionX:" 
                + std::to_string(sprite.getPosition().x) + " positionY:" 
                + std::to_string(sprite.getPosition().y + movementSpeed)).c_str()), serverData);
                std::cout << "client-side: " << std::to_string(this->getUid()) 
                << "\n";
            }
        }
        // Key pressed Space
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            sf::Vector2f pos = sprite.getPosition();
            //audioManager.PlaySound("assets/Sound/enemy_shoot.ogg");
            clock_timer(pos, serverData);
        }
        CharacterEntity::Update(window, serverData);
    }
}

void PlayerEntity::Render(sf::RenderWindow& window, std::vector<mobData>& mobsDatas
, ServerData &serverData)
{
    CharacterEntity::Render(window, mobsDatas, serverData);
    for (auto it = missiles.begin(); it != missiles.end();) {
        auto& m = *it;
        m->Render(window, mobsDatas, serverData);
        if (m->getSpritePosition().x >= window.getSize().x
        || (m->hasReachedTarget() == true)) {
            it = missiles.erase(it);
        } else {
            ++it;
        }
    }
}

void PlayerEntity::clock_timer(sf::Vector2f pos, ServerData &serverData)
{
    seconds = time.asMicroseconds() / 10000.0;
    time = clock.getElapsedTime();

    float movementSpeed = 7.5f;

    if (seconds > 10.5) {
        // addMissile(std::make_unique<MissileEntity>(pos.x, pos.y, MissileEntity::DIRECTION::EAST, 1
        // , this->getUid()));
        // add Missile => just missile's first movement
        commands cmds;
        cmds.sendCommand(const_cast<char *>(std::string("4 " 
        + std::to_string(this->getUid()) + " entityType:Missile"
        + " positionX:" + std::to_string(this->sprite.getPosition().x)
        + " positionY:" + std::to_string(this->sprite.getPosition().y)).c_str()), serverData);
        clock.restart();
    }
}
