/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** main
*/
#include "../include/Game.hpp"

int main(int argc, char **argv)
{
    r_type_client *client;

    if (argc != 2) {
        std::cerr << "Try with: ./r-type_client <ip>\n";
        return (-1);
    }

    client = new r_type_client(8000, argv[1]);
    if (client->bindClientToServer() != 0) {
        std::cout << "Cannot connect to given adress '" << client->getServerIp()
        << ":" << client->getServerPort() << "'\n";
        return (-1);
    }

    std::cout << "Connected to the server (" << argv[1] << ":"
    << client->getServerPort() << ").\n";

    Game *game = new Game(client->getServerPort(), client->getServerIp()
    , client->getClientSocket());

    std::thread receiveThread([client, game]() {
        client->receiveAcknowledgment(game);
    });

    game->Initialize();

    while (game->IsRunning()) {
        game->HandleEvents();
        game->Update();
        game->Render();
    }
    game->getGameEngine().~GameEngine();
    if (game->IsRunning() == false) {
        std::cout << "Disconnected from the server.\n";
        return (-1);
    }
    receiveThread.join();
    return 0;
}
