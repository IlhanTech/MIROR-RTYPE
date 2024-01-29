/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville [WSL: Ubuntu]
** File description:
** r_type_server
*/

#ifndef R_TYPE_SERVER_HPP_
    #define R_TYPE_SERVER_HPP_

    #include <iostream>
    #include <cstring>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <vector>
    #include <thread>

    #include <SFML/Network.hpp>

    #include "Game/Game.hpp"
    #include "Entity/Player/Player.hpp"
    #include "Entity/MissileEntity/MissileEntity.hpp"
    #include "Entity/MobsEntity/MobsEntity.hpp"

    struct c_client {
        sf::IpAddress address;
        unsigned short port;

        // Define the equality operator
        bool operator==(const c_client& other) const {
            return address == other.address && port == other.port;
        }
    };

    class r_type_server
    {
        public:
            r_type_server(int port);
            ~r_type_server();
            int start_server();
            int bindServer();
            int start_server_loop();
            void handleAcknowledgment(int requestId, connectionData connData, int status
            , std::string customResponse);
            void processRequest(char* requestBuffer, size_t bufferSize, c_client clientData);
            void addPlayer(std::unique_ptr<Player> player);
            void addMissile(std::unique_ptr<MissileEntity> missile);
            void addMob(std::unique_ptr<MobsEntity> mob);
            Player *getPlayerByUid(int uniqueId);
            MobsEntity *getMobByUid(int uniqueId);
            MissileEntity *getMissileByUid(int uniqueId);
            int getMissilesSize();
            int getMobsSize();
            std::vector<Player *> getAllPlayers();
            //std::vector<std::unique_ptr<Entity>>& getEntities();
            std::vector<std::unique_ptr<Player>>& getPlayerEntities();
            std::vector<std::unique_ptr<MissileEntity>>& getMissileEntities();
            std::vector<std::unique_ptr<MobsEntity>>& getMobsEntities();
            std::vector<c_client> getConnectedClients();
            sf::UdpSocket& getServerSocket();
            bool checkIfPlayerExists(connectionData connData);
            Game getGame();
            void broadcastMessage(connectionData connData, r_type_server *server, char *buffer);

        private:
            int port;
            sf::UdpSocket serverSocket;
            std::vector<c_client> connectedClients;
            Game game;
            // std::vector<std::unique_ptr<Entity>> entities;
            std::vector<std::unique_ptr<Player>> playerEntities;
            std::vector<std::unique_ptr<MissileEntity>> missileEntities;
            std::vector<std::unique_ptr<MobsEntity>> mobsEntities;
    };

    int generateUniqueId(r_type_server *server, int current_id);

#endif /* !R_TYPE_SERVER_HPP_ */
