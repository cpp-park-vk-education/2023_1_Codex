#include "Listener.hpp"

#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <memory>
#include <string>

#include "Exceptions.hpp"
#include "Session.hpp"
#include "SessionManager.hpp"

namespace Server {

namespace http = boost::beast::http;  // from <boost/beast/http.hpp>
namespace net = boost::asio;          // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;     // from <boost/asio/ip/tcp.hpp>

Listener::Listener(net::io_context &ioc, tcp::endpoint endpoint, std::shared_ptr<std::string const> docRoot)
    : Ioc(ioc), Acceptor(net::make_strand(ioc)), DocRoot(std::move(docRoot)) {
    beast::error_code ec;

    Acceptor.open(endpoint.protocol(), ec);
    if (ec) {
        throw InvalidAcceptorOpen(ec);
    }

    Acceptor.set_option(net::socket_base::reuse_address(true), ec);
    if (ec) {
        throw InvalidAcceptorSetOption(ec);
    }

    Acceptor.bind(endpoint, ec);
    if (ec) {
        throw InvalidAcceptorBind(ec);
    }

    Acceptor.listen(net::socket_base::max_listen_connections, ec);
    if (ec) {
        throw InvalidAcceptorListen(ec);
    }
}

void Listener::Run() {
    DoAccept();
}

void Listener::DoAccept() {
    auto self(shared_from_this());
    Acceptor.async_accept(net::make_strand(Ioc), [this, self](beast::error_code ec, tcp::socket socket) {
        // If error in accept, we accept other connection and skip this failure
        if (!ec) {
            Manager.Run(std::make_shared<Session>(std::move(socket), Manager, DocRoot));
        }
        DoAccept();
    });
}

}  // namespace Server
