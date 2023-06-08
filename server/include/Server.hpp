#pragma once

#include <boost/beast/core.hpp>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "Listener.hpp"

namespace Server {

namespace net = boost::asio;       // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;  // from <boost/asio/ip/tcp.hpp>

class Server {
   public:
    Server(const net::ip::address &address, unsigned short port, std::shared_ptr<std::string const> docRoot,
           int threads);

    void Run();

   private:
    net::io_context Ioc;
    ListenerSPtr Listener;
    std::shared_ptr<std::string const> DocRoot;
    std::vector<std::thread> Threads;
};

}  // namespace Server
