/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** commands
*/

#ifndef COMMANDS_HPP_
#define COMMANDS_HPP_

    #include <iostream>
    #include <vector>
    #include <map>
    #include <functional>

    #include "ServerData.hpp"

    class commands
    {
        public:
            enum CommandType
            {
                CMD_SPAWN_ENTITY,
                CMD_KILL_ENTITY,
                CMD_MOVE_ENTITY,
                CMD_SHOW_ENTITY,
                CMD_UNKOWN
            };

            commands();
            ~commands();

            int sendCommand(char *command, ServerData &serverData);
            int retrieveRequestId(const char *input);

        private:
            std::map<int, std::function<CommandType(int status\
            , char *payload)>> fmap;
    };

#endif /* !COMMANDS_HPP_ */
