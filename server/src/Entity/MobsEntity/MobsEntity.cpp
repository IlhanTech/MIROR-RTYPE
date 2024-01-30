/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** MobsEntity
*/

#include "../../../include/Entity/MobsEntity/MobsEntity.hpp"

MobsEntity::MobsEntity() {}

MobsEntity::MobsEntity(int id) { this->id = id; }

MobsEntity::~MobsEntity() {}

int MobsEntity::getUid()
{
    return (this->id);
}
