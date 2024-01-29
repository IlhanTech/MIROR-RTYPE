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

    #include "../DataStruct/requestData.hpp"
    #include "../DataStruct/connectionData.hpp"
    #include "../r_type_server.hpp"

    class commands
    {
        public:
            commands();
            ~commands();

            enum CommandType
            {
                CMD_SPAWN_ENTITY,
                CMD_KILL_ENTITY,
                CMD_MOVE_ENTITY,
                CMD_SHOW_ENTITY,
                CMD_UNKOWN
            };

            int parseUid(requestData requestData);
            int retrieveCommand(requestData requestData, connectionData connData
            , r_type_server *server, std::string *customResponse);

        private:
            std::map<int, std::function<int(int status\
            , char *payload, r_type_server *server)>> fmap;
    };


#endif /* !COMMANDS_HPP_ */
