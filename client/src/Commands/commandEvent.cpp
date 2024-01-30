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

    // this->commmandPosition(buffer, game);
    std::string payload = buffer;

    std::size_t entityIdPos = payload.find("entityId:");
    std::size_t entityTypePos = payload.find("entityType:");
    std::size_t positionXPos = payload.find("positionX:");
    std::size_t positionYPos = payload.find("positionY:");

    std::string entityId = payload.substr(entityIdPos + 9, entityTypePos - entityIdPos - 10);
    std::string entityType = payload.substr(entityTypePos + 11, positionXPos - entityTypePos - 12);
    std::string positionX = payload.substr(positionXPos + 10, positionYPos - positionXPos - 12);
    std::string positionY = payload.substr(positionYPos + 10);

    if (entityType == "Player") {
        PlayerEntity *player = game->getGameEngine().getPlayerByUid(std::stoi(entityId));

        if (player && player->getUid() != game->getPlayerData().playerUid) {
            player->setPos(Entity::pos{std::stof(positionX), std::stof(positionY)});
        }
    }
    if (entityType == "Missile") {
        MissileEntity *missile = game->getGameEngine().getMissileById(atoi(entityId.c_str()));

        if (!missile) {
            return (0);
        }
        if (missile->getSprite().getPosition().x >= 1075) {
            game->getGameEngine().removeMissile(missile);
            printf("removed missile\n");
            return (0);
        }
        missile->setPos((Entity::pos){static_cast<float>(atof(positionX.c_str()))
        , static_cast<float>(atof(positionY.c_str()))});
    }
    if (entityType == "Mob") {
        MobsEntity *mob = game->getGameEngine().getMobById(atoi(entityId.c_str()));

        if (!mob) {
            return (0);
        }
        if (mob->getSprite().getPosition().x <= -5) {
            game->getGameEngine().removeMob(mob);
            printf("removed mob\n");
            return (0);
        }
        mob->setPos((Entity::pos){static_cast<float>(atof(positionX.c_str()))
            , static_cast<float>(atof(positionY.c_str()))});
    }
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
