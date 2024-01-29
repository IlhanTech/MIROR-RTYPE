/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** Player
*/

#include "../../../include/Entity/Player/Player.hpp"

Player::Player() {}

Player::Player(connectionData datas)
{
    this->setConnectionData(datas);
}

Player::~Player()
{

}

void Player::setGameStateData(gameStateData datas)
{
    this->gStateData = datas;
}

void Player::setConnectionData(connectionData datas)
{
    this->connData = datas;
}

gameStateData Player::getGameStateData()
{
    return this->gStateData;
}

connectionData Player::getConnectionData()
{
    return this->connData;
}

gameplayData Player::getGameplayData()
{
    gameplayData datas;
    datas.entityPos = this->getPosition();
    datas.healthPoints = this->getHealthPoints();
    return datas;
}

pos Player::getPosition()
{
    return this->gamePlay.entityPos;
}
