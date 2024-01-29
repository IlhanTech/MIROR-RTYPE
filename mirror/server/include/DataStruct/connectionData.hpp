/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville [WSL: Ubuntu]
** File description:
** connectionData
*/

#ifndef CONNECTIONDATA_HPP_
    #define CONNECTIONDATA_HPP_

    #include <SFML/Network.hpp>

    struct connectionData {
        int clientUniqueId;
        sf::IpAddress clientAddress;
        unsigned short clientPort;

        bool operator==(const connectionData& connData) const {
            return (clientAddress == connData.clientAddress
            && clientPort == connData.clientPort);
        }
    };

#endif /* !CONNECTIONDATA_HPP_ */
