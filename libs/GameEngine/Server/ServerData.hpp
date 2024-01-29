/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** ServerData
*/

#ifndef SERVERDATA_HPP_
    #define SERVERDATA_HPP_

    #include <SFML/Network.hpp>
    #include <cstring>

    class ServerData {
        public:
            ServerData(int port, sf::IpAddress ip, sf::UdpSocket &socket);
            ~ServerData();
            int getServerPort();
            sf::IpAddress getServerIp();
            sf::UdpSocket &getClientSocket();
        private:
            int port;
            sf::IpAddress serverIp;
            sf::UdpSocket &clientSocket;

            ServerData(const ServerData &) = delete;
            ServerData &operator=(const ServerData &) = delete;
    };

#endif /* !SERVERDATA_HPP_ */
