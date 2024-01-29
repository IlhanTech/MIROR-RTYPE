/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville [WSL: Ubuntu]
** File description:
** command_list
*/

#ifndef COMMAND_LIST_HPP_
    #define COMMAND_LIST_HPP_

    #include <stdio.h>
    #include <vector>

    #include "../DataStruct/requestData.hpp"
    #include "../DataStruct/connectionData.hpp"
    #include "../r_type_server.hpp"

    class command_list
    {
        public:
            command_list();
            ~command_list();
            int handle_connect(requestData reqData, connectionData connData
            , r_type_server *server, std::string *customResponse);
            int handle_play(requestData reqData, connectionData connData
            , r_type_server *server, std::string *customResponse);
            int handle_disconnect(requestData reqData, connectionData connData
            , r_type_server *server, std::string *customResponse);
            int handle_unknown(requestData reqData, connectionData connData
            , r_type_server *server, std::string *customResponse);
            int handle_spawn_entity(requestData reqData, connectionData connData
            , r_type_server *server, std::string *customResponse);
            int handle_position_update(requestData reqData, connectionData connData
            , r_type_server *server, std::string *customResponse);
            int handle_getAllPlayers(requestData reqData, connectionData connData
            , r_type_server *server, std::string *customResponse);
        private:
    };

#endif /* !COMMAND_LIST_HPP_ */
