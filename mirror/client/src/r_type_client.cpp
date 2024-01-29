/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville [WSL: Ubuntu]
** File description:
** r_type_client
*/

#include "../include/r_type_client.hpp"
#include "../include/Game.hpp"

r_type_client::r_type_client(int port, char *address)
{
    this->address = address;
    this->port = port;
}

r_type_client::~r_type_client() {}

sf::UdpSocket &r_type_client::getClientSocket() { return (this->clientSocket); }
sf::IpAddress &r_type_client::getServerIp() { return (this->serverIp); }
int r_type_client::getServerPort() { return (this->port); }

void r_type_client::receiveAcknowledgment(Game *game) {
    while (game->IsRunning()) {

        char buffer[1024];
        std::size_t received;
        sf::IpAddress sender;
        unsigned short senderPort;

        if (this->clientSocket.receive(buffer, sizeof(buffer), received
        , sender, senderPort) == sf::Socket::Done) {
            buffer[received] = '\0';
            std::cout << "[" << sender << ":" << senderPort << "] " << buffer << std::endl;
        }

        // receive fptr
        Commands cmds;
        Commands::parsedBuffer parsedBuf;

        std::cout << "buf: " << buffer << " && requestId: " << parsedBuf.requestId << "\n";

        std::string eventParsing = std::string(buffer).substr(0, 5);
        if (eventParsing == "event") {
            parsedBuf = cmds.parseBasicAcknowledgment(std::string(buffer).substr(6).c_str());
            if (parsedBuf.requestId == 3)
                cmds.handlePlayEvent(std::string(buffer).substr(6).c_str(), game);
            if (parsedBuf.requestId == 4)
                cmds.handleSpawnEntity(std::string(buffer).substr(6).c_str(), game);
            if (parsedBuf.requestId == 7)
                cmds.handleKillEvent(std::string(buffer).substr(6).c_str(), game);
            if (parsedBuf.requestId == 8)
                cmds.handlePositionEvent(std::string(buffer).substr(6).c_str(), game);
        } else {
            parsedBuf = cmds.parseBasicAcknowledgment(buffer);
        }

        if (parsedBuf.requestId == 1) {
            cmds.commmandConnect(buffer, game);
        }
        if (parsedBuf.requestId == 3) {
            cmds.commmandPlay(buffer, game);
        }
        if (parsedBuf.requestId == 4) {
            cmds.commandSpawnEntity(buffer, game);
        }
        if (parsedBuf.requestId == 5) {
            cmds.commmandGetAllMissiles(buffer, game);
        }
        if (parsedBuf.requestId == 6) {
            cmds.commmandGetAllPlayers(buffer, game);
        }
        if (parsedBuf.requestId == 7) {
            cmds.commandKill(buffer, game);
        }
        if (parsedBuf.requestId == 8) {
            cmds.commmandPosition(buffer, game);
        }
        if (parsedBuf.requestId == 9) {
            cmds.commmandGetAllMobs(buffer, game);
        }
    }
}

int r_type_client::bindClientToServer()
{
    this->serverIp = this->address;

    if (this->clientSocket.bind(sf::Socket::AnyPort) != sf::Socket::Done) {
        std::cerr << "Failed to bind the socket to a port" << std::endl;
        return (-1);
    }

    if (this->clientSocket.send("ping", 5, this->serverIp, this->port)
    != sf::Socket::Done) {
        std::cerr << "Failed to connect to the server" << std::endl;
        return (-1);
    }

    char buffer[5];
    std::size_t received;
    sf::IpAddress sender;
    unsigned short senderPort;

    sf::SocketSelector selector;
    selector.add(this->clientSocket);

    sf::Time timeout = sf::seconds(5.0f);

    if (selector.wait(timeout)) {
        if (this->clientSocket.receive(buffer, sizeof(buffer)
        , received, sender, senderPort) != sf::Socket::Done) {
            std::cerr << "Failed to receive response from the server" << std::endl;
            return (-1);
        }
    } else {
        std::cerr << "Ping test timed out" << std::endl;
        return (-1);
    }
    return (0);
}
