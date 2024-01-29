/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** Entity
*/

#include "../../include/Entity/Entity.hpp"

Entity::Entity() {}
Entity::~Entity() {}

void Entity::setGameplayData(gameplayData datas)
{
    this->gPlayData = datas;
    this->position = datas.entityPos;
    this->health = datas.healthPoints;
}
gameplayData Entity::getGameplayData() { return (this->gPlayData); }

int Entity::getHealthPoints() { return this->health; }
void Entity::setHealthPoints(int health) { this->health = health; }

pos Entity::getPosition() { return (this->position); }
void Entity::setPosition(pos position) { this->position = position; }

void Entity::setUid(int uid) { this->uid = uid; }
int Entity::getUid() { return (this->uid); }
