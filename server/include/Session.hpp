#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <memory>
#include <string>

#include "RequestHandler.hpp"

namespace Server {

class SessionManager;

namespace beast = boost::beast;       // from <boost/beast.hpp>
namespace http = boost::beast::http;  // from <boost/beast/http.hpp>
using tcp = boost::asio::ip::tcp;     // from <boost/asio/ip/tcp.hpp>

class Session : public std::enable_shared_from_this<Session> {
   public:
    Session(tcp::socket &&socket, SessionManager &manager, std::shared_ptr<std::string const> docRoot);

    void Run();

    void DoClose();

   private:
    void DoRead();
    void CheckRead(beast::error_code ec, std::size_t bytes_transferred);
    void DoWrite();
    void CheckWrite(beast::error_code ec, std::size_t bytes_transferred);

    beast::tcp_stream Stream;
    beast::flat_buffer Buffer;
    http::request<http::dynamic_body> Request;
    // mb UPtr
    RequestHandler Handler;
    SessionManager &Manager;
    std::shared_ptr<std::string const> DocRoot;
};

using SessionSPtr = std::shared_ptr<Session>;

}  // namespace Server
