/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** MissileEntity
*/

#include "../../../include/Entity/MissileEntity/MissileEntity.hpp"

MissileEntity::MissileEntity() {}

MissileEntity::MissileEntity(int id)
{
    this->id = id;
}

MissileEntity::~MissileEntity() {}

int MissileEntity::getUid()
{
    return (this->id);
}
