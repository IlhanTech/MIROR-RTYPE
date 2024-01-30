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
    game->setPlayerData(pData);
    std::cout << "client uid: " << game->getPlayerData().playerUid << "\n";
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
    // => 'requestId:<6> statusCode:<1> players:<size{uid1,uid2,etc}>'
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
        for (auto& player : game->getGameEngine().getPlayerEntities()) {
            if (uid == player->getUid())
                ++i;
        }
        if (!i) {
            int playerNumber = game->getGameEngine().getPlayersSize() + 1;

            game->getGameEngine().AddPlayer(std::make_unique<PlayerEntity>(PLAYER_SPRITE
            , 200, 300, playerNumber, uid));
        }
    }
    return (0);
}

int Commands::commmandGetAllMissiles(const char *buffer, Game *game)
{
    std::vector<int> missileList;
    // buffer format
    // => 'requestId:<5> statusCode:<1> missiles:<size{uid1,uid2,etc}>'
    // faire une function qui assigne un nouveau sprite au joueur

    parsedBuffer parsedBuf = this->parseBasicAcknowledgment(buffer);
    const char *token = strdup(buffer);
    Game::playerData pData = game->getPlayerData();
    char *tokenizedToken = strtok(const_cast<char *>(token), " ");

    for (int i = 0; i < 2; ++i, tokenizedToken = strtok(nullptr, " "));
    char *playerList = strtok(tokenizedToken, ":");
    playerList = strtok(nullptr, ":");

    char *playerListToken = strtok(playerList, "{");
    if (!playerListToken) {
        return (0);
    }
    int playerNumber = atoi(playerListToken);
    playerListToken = strtok(nullptr, "{");

    if (std::string(playerListToken).find(",") == std::string::npos) {
        char *tokDup = strdup(playerListToken);
        char *tokenizedList = strtok(playerListToken, "}");
        missileList.push_back(atoi(tokenizedList));
    }
    char *tokenizedList = strtok(playerListToken, ",");
    missileList.push_back(atoi(tokenizedList));
    while (tokenizedList = strtok(nullptr, ",")) {
        int pos_substring = 0;
        if ((pos_substring = std::string(tokenizedList).find("}")) != std::string::npos) {
            missileList.push_back(atoi(std::string(tokenizedList).substr(0, pos_substring).c_str()));
            break;
        }
        missileList.push_back(atoi(tokenizedList));
    }
    // set missiles uid
    for (auto& uid: missileList) {
        int i = 0;
        for (auto& missile : game->getGameEngine().getMissileEntities()) {
            if (uid == missile->getId())
                ++i;
        }
        if (!i) {
            int missileNumber = game->getGameEngine().getMissilesSize() + 1;

            // game->getGameEngine().AddPlayer(std::make_unique<PlayerEntity>(PLAYER_SPRITE
            // , 200, 300, playerNumber, uid));
            game->getGameEngine().AddMissile(std::make_unique<MissileEntity>(200, 300
            , MissileEntity::DIRECTION::EAST, missileNumber, uid));
        }
    }
    return (0);
}

int Commands::commmandGetAllMobs(const char *buffer, Game *game)
{
    std::vector<int> mobsList;
    // buffer format
    // => 'requestId:<5> statusCode:<1> missiles:<size{uid1,uid2,etc}>'
    // faire une function qui assigne un nouveau sprite au joueur
    parsedBuffer parsedBuf = this->parseBasicAcknowledgment(buffer);
    const char *token = strdup(buffer);
    Game::playerData pData = game->getPlayerData();
    char *tokenizedToken = strtok(const_cast<char *>(token), " ");

    for (int i = 0; i < 2; ++i, tokenizedToken = strtok(nullptr, " "));
    char *playerList = strtok(tokenizedToken, ":");
    playerList = strtok(nullptr, ":");

    char *playerListToken = strtok(playerList, "{");
    if (!playerListToken) {
        return (0);
    }
    int playerNumber = atoi(playerListToken);
    playerListToken = strtok(nullptr, "{");

    if (std::string(playerListToken).find(",") == std::string::npos) {
        char *tokDup = strdup(playerListToken);
        char *tokenizedList = strtok(playerListToken, "}");
        mobsList.push_back(atoi(tokenizedList));
    }
    char *tokenizedList = strtok(playerListToken, ",");
    mobsList.push_back(atoi(tokenizedList));
    while (tokenizedList = strtok(nullptr, ",")) {
        int pos_substring = 0;
        if ((pos_substring = std::string(tokenizedList).find("}")) != std::string::npos) {
            mobsList.push_back(atoi(std::string(tokenizedList).substr(0, pos_substring).c_str()));
            break;
        }
        mobsList.push_back(atoi(tokenizedList));
    }

    // set missiles uid
    for (auto& uid: mobsList) {
        int i = 0;
        for (auto& mob : game->getGameEngine().getMobEntities()) {
            if (uid == mob->getId())
                ++i;
        }
        if (!i) {
            int mobNumber = game->getGameEngine().getMissilesSize() + 1;

            // game->getGameEngine().AddPlayer(std::make_unique<PlayerEntity>(PLAYER_SPRITE
            // , 200, 300, playerNumber, uid));
            // game->getGameEngine().AddMissile(std::make_unique<MissileEntity>(200, 300
            // , MissileEntity::DIRECTION::EAST, mobNumber, uid));
            game->getGameEngine().AddMob(std::make_unique<MobsEntity>(MOBS1_SPRITE
            , 300, 400, sf::IntRect({5, 0, 21, 24}), false, mobNumber
            , game->getPlayerData().playerUid));
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

    std::string entityId = payload.substr(entityIdPos + 9, entityTypePos - entityIdPos - 10);
    std::string entityType = payload.substr(entityTypePos + 11, positionXPos - entityTypePos - 12);
    std::string positionX = payload.substr(positionXPos + 10, positionYPos - positionXPos - 12);
    std::string positionY = payload.substr(positionYPos + 10);

    if (entityType == "Player") {
        PlayerEntity *player = game->getGameEngine().getPlayerByUid(std::stoi(entityId));
        if (player && player->getUid() == game->getPlayerData().playerUid) {
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

int Commands::commandKill(const char *buffer, Game *game)
{
    std::string payload = buffer;

    std::string entityType;
    std::string entityId;

    printf("[kill buffer] => [%s]\n", payload.c_str());

    std::size_t entityTypePos = payload.find("entityType:");
    if (entityTypePos != std::string::npos) {
        std::size_t entityTypeEndPos = payload.find_first_of(" ", entityTypePos + 11);
        entityType = payload.substr(entityTypePos + 11, entityTypeEndPos - (entityTypePos + 11));
        std::cout << "Entity Type: " << entityType << std::endl;
    }

    std::size_t entityIdPos = payload.find("entityId:");
    if (entityIdPos != std::string::npos) {
        std::size_t entityIdEndPos = payload.find_first_of(" ", entityIdPos + 9);
        entityId = payload.substr(entityIdPos + 9, entityIdEndPos - (entityIdPos + 9));
        std::cout << "Entity Id: " << entityId << std::endl;
    }

    Entity *entity;

    if (entityType == "Missile") {
        entity = game->getGameEngine().getMissileById(atoi(entityId.c_str()));
    }
    if (entityType == "Mob") {
        entity = game->getGameEngine().getMobById(atoi(entityId.c_str()));
    }
    if (entityType == "Player") {
        entity = game->getGameEngine().getPlayerByUid(atoi(entityId.c_str()));
    }
    // game->getGameEngine().removeEntity(entity);
    return (0);
}

int Commands::commandSpawnEntity(const char *buffer, Game *game)
{
    // requestId:4 statusCode:1 entityType:Missile entityId:1
    // positionX:200.000000 positionY:300.000000

    std::string payload = buffer;

    std::size_t entityTypePos = payload.find("entityType:");
    std::size_t entityIdPos = payload.find("entityId:");
    std::size_t positionXPos = payload.find("positionX:");
    std::size_t positionYPos = payload.find("positionY:");

    std::cout << "spawn payload: " << payload << "\n";

    if (entityTypePos != std::string::npos && entityIdPos != std::string::npos &&
        positionXPos != std::string::npos && positionYPos != std::string::npos) {

        std::size_t spaceAfterEntityTypePos = payload.find_first_of(" ", entityTypePos + 11);
        std::string entityType = payload.substr(entityTypePos + 11
        , spaceAfterEntityTypePos - (entityTypePos + 11));

        std::size_t spaceAfterEntityIdPos = payload.find_first_of(" ", entityIdPos + 9);
        std::string entityId = payload.substr(entityIdPos + 9
        , spaceAfterEntityIdPos - (entityIdPos + 9));

        std::size_t spaceAfterPositionXPos = payload.find_first_of(" ", positionXPos + 10);
        std::string positionX = payload.substr(positionXPos + 10
        , spaceAfterPositionXPos - (positionXPos + 10));

        std::string positionY = payload.substr(positionYPos + 10);

        std::cout << "entityType: [" << entityType << "] && entityId: [" << entityId << "] && positionX: [" << positionX << "] && positionY: [" << positionY << "]\n";

        if (entityType == "Missile") {
            game->getGameEngine().AddMissile(std::make_unique<MissileEntity>(
            std::stof(positionX), std::stof(positionY), MissileEntity::DIRECTION::EAST
            , atoi(entityId.c_str()), game->getPlayerData().playerUid));
            std::cout << "new Missile created with id: " <<
            game->getGameEngine().getMissileById(atoi(entityId.c_str()))->getId() << "\n";
        }
        if (entityType == "Mob") {
            game->getGameEngine().AddMob(std::make_unique<MobsEntity>(MOBS1_SPRITE
            , std::stof(positionX), std::stof(positionY), sf::IntRect({5, 0, 21, 24}), false
            , atoi(entityId.c_str()), game->getPlayerData().playerUid));
            std::cout << "new Mob created with id: " <<
            game->getGameEngine().getMobById(atoi(entityId.c_str()))->getId() << "\n";
        }
    }
    return (0);
}
