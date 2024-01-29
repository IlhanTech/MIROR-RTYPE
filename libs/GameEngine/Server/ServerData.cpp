/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** ServerData
*/

#include "ServerData.hpp"

ServerData::ServerData(int port, sf::IpAddress ip, sf::UdpSocket &socket) 
: port(port), serverIp(ip), clientSocket(socket) {}

ServerData::~ServerData() {}

int ServerData::getServerPort()
{
    return (this->port);
}

sf::IpAddress ServerData::getServerIp()
{
    return (this->serverIp);
}

sf::UdpSocket &ServerData::getClientSocket()
{
    return (this->clientSocket);
}
