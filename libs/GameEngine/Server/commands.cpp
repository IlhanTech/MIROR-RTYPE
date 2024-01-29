/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** commands
*/

#include <string.h>
#include "commands.hpp"

commands::commands() {}
commands::~commands() {}

int commands::sendCommand(char *command, ServerData &serverData)
{
    if (serverData.getClientSocket().send(command, std::strlen(command) + 1
    , serverData.getServerIp(), serverData.getServerPort()) != sf::Socket::Done) {
        std::cerr << "Error sending data to server" << std::endl;
        return (-1);
    }
    return (0);
}

int commands::retrieveRequestId(const char *input)
{
    char dest[strlen(input) + 1];
    strcpy(dest, input);
    char *token = strtok(dest, " ");

    std::map<int, const char *> payload_comp = {{1, "connect"}, {2, "disconnect"}\
    , {3, "play"}, {4, "spawnEntity"}, {5, "test"}};

    for (const auto &entry : payload_comp) {
        if (strcmp(entry.second, dest) == 0) {
            printf("%s == req_id : %d\n", entry.second, entry.first);
            return (entry.first);
        }
    }
    return (-1);
}
