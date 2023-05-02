#include "server.hpp"

#include <boost/beast/core.hpp>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "listener.hpp"

namespace Server {

namespace net = boost::asio;       // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;  // from <boost/asio/ip/tcp.hpp>

Server::Server(const net::ip::address &address, unsigned short port,
               std::shared_ptr<std::string const> docRoot, int threads)
    : Ioc(net::io_context{threads}), DocRoot(std::move(docRoot)) {
    Listener = std::make_unique<class Listener>(Ioc, tcp::endpoint{address, port}, DocRoot);

    Threads.reserve(threads - 1);

    net::io_context &ioc = Ioc;
    for (auto i = threads - 1; i > 0; --i) {
        Threads.emplace_back([&ioc] { ioc.run(); });
    }
    Ioc.run();
}

void Server::Run() {
    Listener.get()->Run();
}

}  // namespace Server
