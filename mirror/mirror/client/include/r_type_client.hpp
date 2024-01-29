/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville [WSL: Ubuntu]
** File description:
** r_type_client
*/

#ifndef R_TYPE_CLIENT_HPP_
#define R_TYPE_CLIENT_HPP_

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

#include <SFML/Network.hpp>

class Game;

class r_type_client
{
    public:
        r_type_client(int port, char *address);
        ~r_type_client();
        int bindClientToServer();
        void receiveAcknowledgment(Game *game);
        sf::UdpSocket &getClientSocket();
        sf::IpAddress &getServerIp();
        int getServerPort();
    private:
        int port;
        char *address;
        sf::IpAddress serverIp;
        sf::UdpSocket clientSocket;
};

#endif /* !R_TYPE_CLIENT_HPP_ */
