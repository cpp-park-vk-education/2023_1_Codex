#include <iostream>

#include "client.hpp"

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Usage: client <host> <port> \n"
                  << "Example:\n"
                  << "    client www.example.com 80\n";
        return EXIT_FAILURE;
    }
    auto const host = argv[1];
    auto const port = argv[2];

    Client::Client Client(host, port);

    return 0;
}
