#pragma once

#include <boost/beast/core.hpp>
#include <memory>
#include <string>

#include "Session.hpp"
#include "SessionManager.hpp"

namespace Server {

namespace net = boost::asio;       // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;  // from <boost/asio/ip/tcp.hpp>

class Listener : public std::enable_shared_from_this<Listener> {
   public:
    Listener(net::io_context &ioc, tcp::endpoint endpoint, std::shared_ptr<std::string const> docRoot);

    void Run();

   private:
    void DoAccept();

    net::io_context &Ioc;
    tcp::acceptor Acceptor;
    SessionManager Manager;
    std::shared_ptr<std::string const> DocRoot;
};

using ListenerSPtr = std::shared_ptr<Listener>;

}  // namespace Server
