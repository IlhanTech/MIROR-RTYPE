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
        server->addEntity(std::unique_ptr<Player>(new Player(connData)));
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

int command_list::handle_unknown(requestData reqData, connectionData connData
, r_type_server *server, std::string *customResponse)
{
    printf("unkown erz\n");
    server->broadcastMessage(connData, server, (char *)"[server] broadcast test");
    return (2);
}

int command_list::handle_spawn_entity(requestData reqData, connectionData connData
, r_type_server *server, std::string *customResponse)
{
    printf("spawn_entity yoow\n");
    return (1);
}

int command_list::handle_position_update(requestData reqData, connectionData connData
, r_type_server *server, std::string *customResponse)
{
    //format: requestId:<id> entityType:<Player:else> entityId:<mobId:playerUid> positionX:<x> positionY<y>

    std::string payload = reqData.payload;

    printf("testa\n");
    printf("here %d && %d\n", reqData.requestId, connData.clientUniqueId);

    std::string entityId = std::to_string(connData.clientUniqueId);

    std::size_t entityTypePos = payload.find("entityType:");
    std::size_t positionXPos = payload.find("positionX:");
    std::size_t positionYPos = payload.find("positionY:");

    // Check if substrings are found
    if (entityTypePos != std::string::npos && positionXPos != std::string::npos && positionYPos != std::string::npos) {
        // Extracting substrings
        std::string entityType = payload.substr(entityTypePos + 11, positionXPos - (entityTypePos + 12));
        std::string positionX = payload.substr(positionXPos + 10, positionYPos - (positionXPos + 11));
        std::string positionY = payload.substr(positionYPos + 10);

        // Rest of the code remains the same...
        // ...

        Entity *entity;

        printf("lola1 [%s]\n", entityType.c_str());
        if (entityType == "Player")
            entity = server->getPlayerByUid(atoi(entityId.c_str()));
        if (entityType == "MobsEntity")
            entity = server->getEntityByUid(atoi(entityId.c_str()));

        printf("lola2 [%s] && [%s]\n", positionX.c_str(), positionY.c_str());
        entity->setGameplayData((gameplayData){entity->getGameplayData().healthPoints,
                                            (pos){static_cast<float>(atof(positionX.c_str())), static_cast<float>(atof(positionY.c_str()))}});
        printf("lola3\n");

        *customResponse = "requestId:8 statusCode:1 entityId:" + entityId + " entityType:" 
        + entityType + " positionX:" + positionX + " positionY:" + positionY;
        printf("lola4\n");
        std::cout << "customResponse: " << *customResponse << "\n";
        std::string broadcastPayload = "event " + *customResponse;
        server->broadcastMessage(connData, server, const_cast<char *>(broadcastPayload.c_str()));
    }
    return (1);
}

int command_list::handle_getAllPlayers(requestData reqData, connectionData connData
, r_type_server *server, std::string *customResponse)
{
    std::string playerList = "{";

    int i = 0;
    for (auto& player : server->getAllPlayers()) {
        printf("curr: %d\n", player->getConnectionData().clientUniqueId);
        playerList = playerList + (i++ ? "," : "")
        + std::to_string(player->getConnectionData().clientUniqueId);
    }
    playerList = playerList + "}";
    *customResponse = playerList;
    printf("customResponse: [%s]\n", customResponse->c_str());
    return (1);
}
