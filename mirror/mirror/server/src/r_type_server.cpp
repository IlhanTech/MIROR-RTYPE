/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville [WSL: Ubuntu]
** File description:
** r_type_server
*/

#include "../include/r_type_server.hpp"
#include "../include/commands/commands.hpp"
#include "../include/DataStruct/requestData.hpp"
#include "../include/DataStruct/connectionData.hpp"

r_type_server::r_type_server(int port) { this->port = port; }
r_type_server::~r_type_server() {}

Game r_type_server::getGame() { return (this->game); }

void r_type_server::addEntity(std::unique_ptr<Entity> entity)
{ this->entities.push_back(std::move(entity)); }

std::vector<Player *> r_type_server::getAllPlayers()
{
    std::vector<Player *> players;

    for (auto &entity : this->entities) {
        if (Player *player = dynamic_cast<Player *>(entity.get())) {
            players.emplace_back(player);
        }
    }
    return (players);
}

std::vector<c_client> r_type_server::getConnectedClients()
{
    return (this->connectedClients);
}

sf::UdpSocket& r_type_server::getServerSocket()
{
    return (this->serverSocket);
}

Player *r_type_server::getPlayerByUid(int uniqueId)
{
    for (auto &entity : this->entities) {
        if (Player *player = dynamic_cast<Player *>(entity.get())) {
            if (player->getConnectionData().clientUniqueId == uniqueId)
                return (player);
        }
    }
    return (nullptr);
}

Entity *r_type_server::getEntityByUid(int uniqueId)
{
    for (auto& entity : this->entities) {
        if (entity->getUid() == uniqueId) {
            return (entity.get());
        }
    }
    return (nullptr);
}

std::vector<std::unique_ptr<Entity>>& r_type_server::getEntities()
{ return (this->entities); }

bool r_type_server::checkIfPlayerExists(connectionData connData)
{
    for (auto& entity : this->getEntities()) {
        if (Player *player = dynamic_cast<Player *>(entity.get())) {
            if (player->getConnectionData().clientAddress == connData.clientAddress
            && player->getConnectionData().clientPort == connData.clientPort) {
                if (player->getConnectionData().clientUniqueId != -1)
                    return (true);
            }
        }
    }
    return (false);
}

void r_type_server::broadcastMessage(connectionData connData, r_type_server *server, char *buffer)
{
    for (const auto& player : server->getAllPlayers()) {
        if (!(player->getConnectionData() == connData)) {
            server->serverSocket.send(buffer, std::strlen(buffer) + 1
            ,player->getConnectionData().clientAddress
            , player->getConnectionData().clientPort);
            printf("[BROADCAST SENT]: [%s]\n", buffer);
        }
    }
}

void r_type_server::handleAcknowledgment(int requestId, connectionData connData, int status
, std::string customResponse)
{
    std::string response = "requestId:" + std::to_string(requestId)
    + " statusCode:" + std::to_string(status);

    // play
    if (requestId == 3) {
        response = response + " playerNumber:" + std::to_string(this->getAllPlayers().size());
    }
    if (requestId == 8) {
        response = customResponse;
    }
    if (requestId == 6) {
        response = response + " players:" + std::to_string(this->getAllPlayers().size()) 
        + customResponse;
    }
    this->serverSocket.send(response.c_str(), response.size(), connData.clientAddress, connData.clientPort);
    printf("sent response: [%s]\n",response.c_str());
}

void r_type_server::processRequest(char* buffer, size_t bufferSize, c_client clientData)
{
    commands cmd;
    char *buffer_tmp = strdup(buffer);
    char *token = std::strtok(buffer_tmp, " ");
    if (token == nullptr) {
        printf("wrong format\n");
        return;
    }
    int requestId = atoi(token);

    if (!requestId) {
        printf("no request ID\n");
        return;
    }

    connectionData connData;
    connData.clientAddress = clientData.address;
    connData.clientPort = clientData.port;

    std::string customResponse;

    int statusCode = cmd.retrieveCommand((requestData){requestId, buffer}
    , connData, this, &customResponse);

    // Acknowledgment Part
    if (statusCode != -1)
        r_type_server::handleAcknowledgment(requestId, connData, statusCode, customResponse);
}

int r_type_server::bindServer()
{
    if (this->serverSocket.bind(this->port) != sf::Socket::Done) {
        std::cerr << "Error while binding to port " << this->port << std::endl;
        return (-1);
    }
    return (0);
}

int r_type_server::start_server_loop()
{
    while (true) {
        sf::IpAddress sender;
        unsigned short senderPort;
        char buffer[1024];
        std::size_t bufferSize;

        if (this->serverSocket.receive(buffer, sizeof(buffer), bufferSize, sender, senderPort) != sf::Socket::Done) {
            std::cerr << "Error receiving data from client" << std::endl;
        } else {
            c_client client = {sender, senderPort};

            if (std::string(buffer) == "ping") {
                std::string pingResponse = "pong";
                this->serverSocket.send(pingResponse.c_str(), pingResponse.size() + 1
                , sender, senderPort);
                continue;
            }
            if (std::string(buffer) == "test") {
                printf("breoadcast test\n");
                std::string pingResponse = "[BROADCAST]\n";
                for (const auto& player : this->getAllPlayers()) {
                    this->serverSocket.send(buffer, std::strlen(buffer) + 1
                    ,player->getConnectionData().clientAddress
                    , player->getConnectionData().clientPort);
                }
                continue;
            }

            printf("buffer: [%s]\n", buffer);

            this->processRequest(buffer, bufferSize, client);

            if (std::find(this->connectedClients.begin(), this->connectedClients.end()
            , client) == this->connectedClients.end()) {
                this->connectedClients.push_back(client);
            }
        }
    }
    return (0);
}

int r_type_server::start_server() {
    int return_value = 0;

    if ((return_value = r_type_server::bindServer()) != 0)
        return (return_value);
    std::cout << "Server is listening on port " << this->port << std::endl;
    if ((return_value = r_type_server::start_server_loop()) != 0)
        return (return_value);
    return (return_value);
}
