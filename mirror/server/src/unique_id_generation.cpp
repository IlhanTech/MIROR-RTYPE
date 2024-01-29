/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville [WSL: Ubuntu]
** File description:
** unique_id_generation
*/

#include <iostream>
#include <random>

#include "../include/r_type_server.hpp"

int generateUniqueId(r_type_server *server, int current_id)
{
    int uniqueId = 0;

    if (current_id != -1) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(1, 99);

        uniqueId = distribution(gen);
        if (uniqueId == current_id)
            return (uniqueId = generateUniqueId(server, uniqueId));
        return (uniqueId);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 99);

    uniqueId = distribution(gen);
    for (auto& player : server->getPlayerEntities()) {
        if (player->getConnectionData().clientUniqueId == uniqueId)
            return (uniqueId = generateUniqueId(server, uniqueId));
    }
    return (uniqueId);
}
