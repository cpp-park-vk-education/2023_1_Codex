#include "Server.hpp"

namespace Server {

Server::Server(const net::ip::address &address, unsigned short port,
               std::shared_ptr<std::string const> docRoot, int threads)
    : Ioc(net::io_context{threads}), DocRoot(std::move(docRoot)) {
    Listener = std::make_shared<class Listener>(Ioc, tcp::endpoint{address, port}, DocRoot);
}

void Server::Run() {
    Listener.get()->Run();

    Threads.reserve(1 - 1);

    net::io_context &ioc = Ioc;
    for (auto i = 1 - 1; i > 0; --i) {
        Threads.emplace_back([&ioc] { ioc.run(); });
    }
    Ioc.run();
}

}  // namespace Server
