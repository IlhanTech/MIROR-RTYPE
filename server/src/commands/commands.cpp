/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** commands
*/

#include "./../../include/commands/commands.hpp"
#include "./../../include/commands/command_list.hpp"

commands::commands()
{
}

commands::~commands()
{
}

int commands::parseUid(requestData reqData)
{
    char *buffer_tmp = strdup(reqData.payload);
    char *token = std::strtok(buffer_tmp, " ");
    if (token == nullptr) {
        printf("wrong format uid 1\n");
        return (-1);
    }
    token = std::strtok(nullptr, " ");
    if (token == nullptr) {
        printf("wrong format uid 2\n");
        return (-1);
    }
    int uniqueId = atoi(token);

    if (!uniqueId)
        return (-1);
    return (uniqueId);
}

int commands::retrieveCommand(requestData reqData, connectionData connData
, r_type_server *server, std::string *customResponse)
{
    int playerUid = 0;
    int requestId = 0;
    int statusCode = 0;

    typedef int (command_list::*cmdFptr)(requestData reqData, connectionData connData
    , r_type_server *server, std::string *customResponse);
    cmdFptr fptr[9] = {
        &command_list::handle_connect,
        &command_list::handle_disconnect,
        &command_list::handle_play,
        &command_list::handle_spawn_entity,
        &command_list::handle_getAllMissiles,
        &command_list::handle_getAllPlayers,
        &command_list::handle_kill,
        &command_list::handle_position_update,
        &command_list::handle_getAllMobs
    };

    int req_index[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    command_list cmd;

    for (int i = 0; i < 9; i++) {
        if (reqData.requestId == req_index[i]) {
            if (i != 0)
                if ((playerUid = parseUid(reqData)) == -1)
                    return (-1);
            connData.clientUniqueId = playerUid;
            statusCode = (cmd.*fptr[i])(reqData, connData
            , server, customResponse);
        }
    }
    return (statusCode);
}
