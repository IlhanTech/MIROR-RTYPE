/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "../Entity.hpp"
#include "../../DataStruct/connectionData.hpp"
#include "../../DataStruct/gameStateData.hpp"
#include "../../DataStruct/gameplayData.hpp"

class Player : public Entity {
public:
    Player();
    explicit Player(connectionData datas);
    virtual ~Player();

    void setConnectionData(connectionData datas);
    void setGameStateData(gameStateData datas);
    connectionData getConnectionData();
    gameStateData getGameStateData();
    pos getPosition();
    gameplayData getGameplayData();

private:
    connectionData connData;
    gameStateData gStateData;
    gameplayData gamePlay;
};

#endif /* !PLAYER_HPP_ */
