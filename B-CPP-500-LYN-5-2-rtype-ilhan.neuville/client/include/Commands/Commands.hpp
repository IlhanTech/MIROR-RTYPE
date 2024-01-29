/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville [WSL: Ubuntu]
** File description:
** Commands
*/

#ifndef COMMANDS_client_HPP_
    #define COMMANDS_client_HPP_

    #include "../Game.hpp"

    class Commands {
        public:
            struct parsedBuffer {
                int requestId;
                int statusCode;
            };

            Commands();
            ~Commands();

            parsedBuffer parseBasicAcknowledgment(const char *buffer);

            int handlePlayEvent(const char *buffer, Game *game);
            int handlePositionEvent(const char *buffer, Game *game);

            int commmandConnect(const char *buffer, Game *game);
            int commmandPlay(const char *buffer, Game *game);
            int commmandGetAllPlayers(const char *buffer, Game *game);
            int commmandPosition(const char *buffer, Game *game);
        private:
    };

#endif /* !COMMANDS_client_HPP_ */
