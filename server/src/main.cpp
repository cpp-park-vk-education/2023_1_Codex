#include <boost/beast/core.hpp>
#include <iostream>
#include <memory>

#include "Exceptions.hpp"
#include "Server.hpp"

namespace net = boost::asio;  // from <boost/asio.hpp>

int main(int argc, char *argv[]) {
    // if (argc != 5) {
    //     std::cerr << "Usage: server <address> <port> <doc_root> <threads>\n"
    //               << "Example:\n"
    //               << "    server 0.0.0.0 8080 . 1\n";
    //     return EXIT_FAILURE;
    // }
    // auto address = net::ip::make_address(argv[1]);
    // auto port = static_cast<unsigned short>(std::atoi(argv[2]));
    // auto docRoot = std::make_shared<std::string>(argv[3]);
    // auto threads = std::max<int>(1, std::atoi(argv[4]));

    auto address = net::ip::make_address("127.0.0.1");
    auto port = static_cast<unsigned short>(std::atoi("7273"));
    auto docRoot = std::make_shared<std::string>("./models");
    auto threads = std::max<int>(1, std::atoi("1"));

    try {
        Server::Server server(address, port, docRoot, threads);

        server.Run();
    } catch (const Server::ServerException &ex) {
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}
