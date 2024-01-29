#include "../include/r_type_server.hpp"

int main(int argc, char **argv)
{
    int port = 0;

    if (argc != 2 || strlen(argv[1]) != 4) {
        std::cout << "Usage: ./server <port>\n";
        return (-1);
    }
    port = atoi(argv[1]);
    if (port != 0) {
        r_type_server *server = new r_type_server(port);
        return (server->start_server());
    }
    return (-1);
}
