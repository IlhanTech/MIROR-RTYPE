/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville [WSL: Ubuntu]
** File description:
** commandEvent
*/

#include "../../include/Commands/Commands.hpp"

int Commands::handlePlayEvent(const char *buffer, Game *game)
{
    this->commmandGetAllPlayers(buffer, game);
    return (0);
}

int Commands::handlePositionEvent(const char *buffer, Game *game)
{
    // format => requestId:<id> statusCode:<code> entityType:<Player:else> 
    // EntityId:<mobId:playerUid> positionX:<x> positionY<y>

    this->commmandPosition(buffer, game);
    return (0);
}

int Commands::handleKillEvent(const char *buffer, Game *game)
{
    this->commandKill(buffer, game);
    return (0);
}

int Commands::handleSpawnEntity(const char *buffer, Game *game)
{
    this->commandSpawnEntity(buffer, game);
    return (0);
}
