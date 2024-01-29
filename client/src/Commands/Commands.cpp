/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville [WSL: Ubuntu]
** File description:
** Commands
*/

#include "../../include/Commands/Commands.hpp"
#include "../../../libs/GameEngine/Entities/Entity.hpp"

Commands::Commands()
{
}

Commands::~Commands()
{
}

Commands::parsedBuffer Commands::parseBasicAcknowledgment(const char *buffer)
{
    parsedBuffer parsedBuf;

    char *tokenDup = strdup(buffer);
    char *token = strtok(const_cast<char *>(tokenDup), " ");
    while (token != nullptr) {
        std::string entry(token);

        size_t pos = entry.find("requestId:");
        if (pos != std::string::npos) {
            parsedBuf.requestId = std::stoi(entry.substr(pos + (strlen("requestId:"))));
        }

        pos = entry.find("statusCode:");
        if (pos != std::string::npos) {
            parsedBuf.statusCode = std::stoi(entry.substr(pos + (strlen("statusCode:"))));
        }
        token = strtok(nullptr, " ");
    }
    return (parsedBuf);
}

int Commands::commmandConnect(const char *buffer, Game *game)
{
    // buffer format
    // => 'requestId:<id> statusCode:<status>'
    Game::playerData pData = game->getPlayerData();
    parsedBuffer parsedBuf = this->parseBasicAcknowledgment(buffer);

    pData.playerUid = parsedBuf.statusCode;
    pData.isConnected = true;
    pData.isPlaying = false;
    printf("playerUid: %d == %d\n", pData.playerUid, parsedBuf.statusCode);
    game->setPlayerData(pData);
    return (0);
}

int Commands::commmandPlay(const char *buffer, Game *game)
{
    // buffer format
    // => 'requestId:<id> statusCode:<status> playerNumber:<player's Number>'
    // faire une function qui assigne un nouveau sprite au joueur
    parsedBuffer parsedBuf = this->parseBasicAcknowledgment(buffer);
    const char *token = strdup(buffer);
    Game::playerData pData = game->getPlayerData();
    char *tokenizedToken = strtok(const_cast<char *>(token), " ");

    for (int i = 0; i < 2; ++i, tokenizedToken = strtok(nullptr, " "));
    char *playerNumberToken = strtok(tokenizedToken, ":");
    playerNumberToken = strtok(nullptr, ":");
    int playerNumber = atoi(playerNumberToken);

    pData.x = 200;
    pData.y = 300;
    pData.isPlaying = true;
    game->setPlayerData(pData);
    // pData.sprite = assignNewSprite(playerNumber);
    return (0);
}

int Commands::commmandGetAllPlayers(const char *buffer, Game *game)
{
    std::vector<int> playerUidList;
    // buffer format
    // => 'requestId:<5> statusCode:<1> players:<size{uid1,uid2,etc}>'
    // faire une function qui assigne un nouveau sprite au joueur
    parsedBuffer parsedBuf = this->parseBasicAcknowledgment(buffer);
    const char *token = strdup(buffer);
    Game::playerData pData = game->getPlayerData();
    char *tokenizedToken = strtok(const_cast<char *>(token), " ");

    for (int i = 0; i < 2; ++i, tokenizedToken = strtok(nullptr, " "));
    char *playerList = strtok(tokenizedToken, ":");
    playerList = strtok(nullptr, ":");

    char *playerListToken = strtok(playerList, "{");
    int playerNumber = atoi(playerListToken);
    playerListToken = strtok(nullptr, "{");

    if (std::string(playerListToken).find(",") == std::string::npos) {
        char *tokDup = strdup(playerListToken);
        char *tokenizedList = strtok(playerListToken, "}");
        playerUidList.push_back(atoi(tokenizedList));
    }
    char *tokenizedList = strtok(playerListToken, ",");
    playerUidList.push_back(atoi(tokenizedList));
    while (tokenizedList = strtok(nullptr, ",")) {
        int pos_substring = 0;
        if ((pos_substring = std::string(tokenizedList).find("}")) != std::string::npos) {
            playerUidList.push_back(atoi(std::string(tokenizedList).substr(0, pos_substring).c_str()));
            break;
        }
        playerUidList.push_back(atoi(tokenizedList));
    }

    // set players uid
    for (auto& uid: playerUidList) {
        int i = 0;
        for (auto& entity : game->getGameEngine().getEntities()) {
            if (PlayerEntity *player = dynamic_cast<PlayerEntity *>(entity.get())) {
                if (uid == player->getUid())
                    ++i;
            }
        }
        if (!i) {
            int playerNumber = game->getGameEngine().getPlayersSize() + 1;

            std::unique_ptr<PlayerEntity> playerEntity = std::make_unique<PlayerEntity>(PLAYER_SPRITE
            , 200, 300, playerNumber);
            playerEntity->setUid(uid);
            game->getGameEngine().AddEntity(std::move(playerEntity));
        }
    }
    return (0);
}

int Commands::commmandPosition(const char *buffer, Game *game)
{
    // format: requestId:<id> statusCode<status> entityType:<Player:else>
    // entityId:<mobId:playerUid> positionX:<x> positionY:<y>

    std::string payload = buffer;

    std::size_t entityIdPos = payload.find("entityId:");
    std::size_t entityTypePos = payload.find("entityType:");
    std::size_t positionXPos = payload.find("positionX:");
    std::size_t positionYPos = payload.find("positionY:");

    // Extracting substrings
    std::string entityId = payload.substr(entityIdPos + 9, entityTypePos - entityIdPos - 10);
    std::string entityType = payload.substr(entityTypePos + 11, positionXPos - entityTypePos - 12);
    std::string positionX = payload.substr(positionXPos + 10, positionYPos - positionXPos - 12);
    std::string positionY = payload.substr(positionYPos + 10);

    std::cout << "entityId: [" << entityId << "] && type: [" << entityType <<
    "] && posX: [" << positionX << "] && posY: [" << positionY << "]\n";
    if (entityType == "Player") {
        PlayerEntity *player = game->getGameEngine().getPlayerByUid(atoi(entityId.c_str()));

        printf("posx: %s && posY: %s\n", positionX.c_str(), positionY.c_str());
        player->setPos((Entity::pos){static_cast<float>(atof(positionX.c_str()))
        , static_cast<float>(atof(positionY.c_str()))});
    }
    return (0);
}