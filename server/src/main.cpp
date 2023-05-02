#include <iostream>
#include <memory>

#include "server.hpp"

namespace net = boost::asio;  // from <boost/asio.hpp>

int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: server <address> <port> <doc_root> <threads>\n"
                  << "Example:\n"
                  << "    server 0.0.0.0 8080 . 1\n";
        return EXIT_FAILURE;
    }
    auto address = net::ip::make_address(argv[1]);
    auto port = static_cast<unsigned short>(std::atoi(argv[2]));
    auto docRoot = std::make_shared<std::string>(argv[3]);
    auto threads = std::max<int>(1, std::atoi(argv[4]));

    // try-catch
    Server::Server server(address, port, docRoot, threads);

    return 0;
}
