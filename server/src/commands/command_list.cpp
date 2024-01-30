/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville [WSL: Ubuntu]
** File description:
** command_list
*/

#include "../../include/commands/command_list.hpp"
#include "../../include/r_type_server.hpp"

command_list::command_list()
{
}

command_list::~command_list()
{
}

int command_list::handle_connect(requestData reqData, connectionData connData
, r_type_server *server, std::string *customResponse)
{
    int uniqueId = generateUniqueId(server, -1);

    connData.clientUniqueId = uniqueId;

    if (server->checkIfPlayerExists(connData) != true) {
        server->addPlayer(std::unique_ptr<Player>(new Player(connData)));
        server->getPlayerByUid(uniqueId)->setGameStateData((gameStateData) {
                true, false, false, false, false, 0
            });
        return (uniqueId);
    }
    return (-1);
}

int command_list::handle_disconnect(requestData reqData, connectionData connData
, r_type_server *server, std::string *customResponse)
{
    printf("disconnect cmd\n");
    return (2);
}

int command_list::handle_play(requestData reqData, connectionData connData
, r_type_server *server, std::string *customResponse)
{
    Player *player = server->getPlayerByUid(connData.clientUniqueId);
    gameStateData playerGameState = player->getGameStateData();

    playerGameState.isPlaying = true;
    player->setGameStateData(playerGameState);

    handle_getAllPlayers(reqData, connData, server, customResponse);
    std::string broadcastPayload = "event requestId:3 statusCode:1 players:"
    + std::to_string(server->getAllPlayers().size()) + *customResponse;

    server->broadcastMessage(connData, server, const_cast<char *>(broadcastPayload.c_str()));
    return (1);
}

int command_list::handle_getAllMobs(requestData reqData, connectionData connData
, r_type_server *server, std::string *customResponse)
{
    std::string mobList = "{";

    int i = 0;
    for (auto& mob : server->getMobsEntities()) {
        printf("currMob: %d\n", mob->getUid());
        mobList = mobList + (i++ ? "," : "")
        + std::to_string(mob->getUid());
    }
    mobList = mobList + "}";
    *customResponse = mobList;
    printf("customResponse: [%s]\n", customResponse->c_str());
    return (1);
}

int command_list::handle_spawn_entity(requestData reqData, connectionData connData
, r_type_server *server, std::string *customResponse)
{
    //format: 4 80 entityType:Missile positionX:185.000000 positionY:165.000000
    std::string payload = reqData.payload;

    std::size_t entityTypePos = payload.find("entityType:");
    std::size_t positionXPos = payload.find("positionX:");
    std::size_t positionYPos = payload.find("positionY:");

    if (entityTypePos != std::string::npos) {
        std::size_t spaceAfterEntityTypePos = payload.find_first_of(" ", entityTypePos + 11);
        std::string entityType = payload.substr(entityTypePos + 11, spaceAfterEntityTypePos - (entityTypePos + 11));

        std::size_t spaceAfterPositionXPos = payload.find_first_of(" ", positionXPos + 10);
        std::string positionX = payload.substr(positionXPos + 10, spaceAfterPositionXPos - (positionXPos + 10));

        std::size_t spaceAfterPositionYPos = payload.find_first_of(" ", positionYPos + 10);
        std::string positionY = payload.substr(positionYPos + 10, spaceAfterPositionYPos - (positionYPos + 10));

        std::string entityId;

        std::cout << "entityType: [" << entityType << "] && positionX: [" << positionX << "] && positionY: [" << positionY << "]\n";

        if (entityType == "Missile") {
            int missileSize = server->getMissilesSize();
            server->addMissile(std::make_unique<MissileEntity>(++missileSize));
            entityId = std::to_string(missileSize);
        }
        else if (entityType == "Mob") {
            int mobSize = server->getMobsSize();
            server->addMob(std::make_unique<MobsEntity>(++mobSize));
            entityId = std::to_string(mobSize);
        }

        *customResponse = "requestId:4 statusCode:1 entityType:" + entityType
        + " entityId:" + entityId + " positionX:" + positionX + " positionY:" + positionY;
    }
    return (1);
}

int command_list::handle_position_update(requestData reqData, connectionData connData
, r_type_server *server, std::string *customResponse)
{
    //format: requestId:<id> entityType:<Player:else> entityId:<mobId:playerUid> positionX:<x> positionY<y>

    std::string payload = reqData.payload;

    // printf("handle_position_update [%s]\n", payload.c_str());

    std::size_t entityIdPos = payload.find("entityId:");
    std::size_t entityTypePos = payload.find("entityType:");
    std::size_t positionXPos = payload.find("positionX:");
    std::size_t positionYPos = payload.find("positionY:");

    // Check if substrings are found
    if (entityTypePos != std::string::npos && positionXPos != std::string::npos && positionYPos != std::string::npos) {
        // Extracting substrings
        std::string entityType = payload.substr(entityTypePos + 11, entityIdPos - (entityTypePos + 12));
        std::string entityId = payload.substr(entityIdPos + 9, positionXPos - (entityIdPos + 10));
        std::string positionX = payload.substr(positionXPos + 10, positionYPos - (positionXPos + 11));
        std::string positionY = payload.substr(positionYPos + 10);

        // Rest of the code remains the same...
        // ...

        Entity *entity;

        if (entityType == "Player") {
            Player *player = server->getPlayerByUid(atoi(entityId.c_str()));

            if (connData.clientUniqueId == player->getUid()) {
                *customResponse = "requestId:8 statusCode:1 entityId:" 
                + std::to_string(connData.clientUniqueId) + " entityType:" 
                + entityType + " positionX:" + positionX + " positionY:" + positionY;
                std::string broadcastPayload = "event " + *customResponse;
                server->broadcastMessage(connData, server
                , const_cast<char *>(broadcastPayload.c_str()));
                return (0);
            }

        }
        // if (entityType == "Missile") {
        //     MissileEntity *missile = server->getMissileByUid(atoi(entityId.c_str()));

        //     *customResponse = "requestId:8 statusCode:1 entityId:" + entityId 
        //     + " entityType:" + entityType + " positionX:" + positionX 
        //     + " positionY:" + positionY;
        //     std::string broadcastPayload = "event " + *customResponse;
        //     server->broadcastMessage(connData, server
        //     , const_cast<char *>(broadcastPayload.c_str()));
        // }
        // if (entityType == "Mob") {
        //     entity = server->getMobByUid(atoi(entityId.c_str()));
        //     if (!entity) {
        //         // créer le mob
        //         int mobSize = server->getMobsSize();
        //         server->addEntity(std::make_unique<MobsEntity>(++mobSize));
        //         entityId = std::string(std::to_string(mobSize));
        //         entity = server->getMobByUid(atoi(entityId.c_str()));
        //     }
        // }

        if (stof(positionX) >= 1075) {
            // std::vector<std::unique_ptr<Entity>> &entities = server->getEntities();

            // auto it = std::find_if(entities.begin(), entities.end()
            // , [entity](const std::unique_ptr<Entity>& e) {
            //     return e.get() == entity;
            // });
            // if (it != entities.end()) {
            //     entities.erase(it);
            // }
            // printf("removed entity serverside with id: %s\n", entityId);
        }

        *customResponse = "requestId:8 statusCode:1 entityId:" + entityId + " entityType:"
        + entityType + " positionX:" + positionX + " positionY:" + positionY;

        // std::cout << "customResponse: " << *customResponse << "\n";
        std::string broadcastPayload = "event " + *customResponse;
        // server->broadcastMessage(connData, server, const_cast<char *>(broadcastPayload.c_str()));
    }
    return (1);
}

int command_list::handle_getAllPlayers(requestData reqData, connectionData connData
, r_type_server *server, std::string *customResponse)
{
    std::string playerList = "{";

    int i = 0;
    for (auto& player : server->getAllPlayers()) {
        printf("currPlayer: %d\n", player->getConnectionData().clientUniqueId);
        playerList = playerList + (i++ ? "," : "")
        + std::to_string(player->getConnectionData().clientUniqueId);
    }
    playerList = playerList + "}";
    *customResponse = playerList;
    printf("customResponse: [%s]\n", customResponse->c_str());
    return (1);
}

int command_list::handle_getAllMissiles(requestData reqData, connectionData connData
, r_type_server *server, std::string *customResponse)
{
    std::string missileList = "{";

    int i = 0;
    for (auto& missile : server->getMissileEntities()) {
        printf("currMissile: %d\n", missile->getUid());
        missileList = missileList + (i++ ? "," : "")
        + std::to_string(missile->getUid());
    }
    missileList = missileList + "}";
    *customResponse = missileList;
    printf("customResponse: [%s]\n", customResponse->c_str());
    return (1);
}

int command_list::handle_kill(requestData reqData, connectionData connData
, r_type_server *server, std::string *customResponse)
{
    // payload format: <requestId> '<clientUid> entityType:<Player:Mob:Missile> 
    // EntityId:<mobId:playerUId:missileId>'
    std::string payload = reqData.payload;

    std::cout << "payload kill: [" << payload << "]\n";

    std::string entityType;
    std::string entityId;

    std::size_t entityTypePos = payload.find("entityType:");
    if (entityTypePos != std::string::npos) {
        std::size_t entityTypeEndPos = payload.find_first_of(" ", entityTypePos + 11);
        entityType = payload.substr(entityTypePos + 11, entityTypeEndPos - (entityTypePos + 11));
        std::cout << "Entity Type: " << entityType << std::endl;
    }

    std::size_t entityIdPos = payload.find("EntityId:");
    if (entityIdPos != std::string::npos) {
        std::size_t entityIdEndPos = payload.find_first_of(" ", entityIdPos + 9);
        entityId = payload.substr(entityIdPos + 9, entityIdEndPos - (entityIdPos + 9));
        std::cout << "Entity Id: " << entityId << std::endl;
    }

    *customResponse = "requestId:" + std::to_string(reqData.requestId) + " statusCode:1 " 
    + "entityType:"+ entityType + " entityId:" + entityId;
    server->broadcastMessage(connData, server, const_cast<char *>(std::string("event " 
    + *customResponse).c_str()));
    return (1);
}
