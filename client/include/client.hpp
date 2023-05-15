#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <memory>
#include <string>

#include "taskInfo.hpp"

namespace Client {

namespace beast = boost::beast;       // from <boost/beast.hpp>
namespace http = boost::beast::http;  // from <boost/beast/http.hpp>
namespace net = boost::asio;          // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;     // from <boost/asio/ip/tcp.hpp>

class Client {
   public:
    Client(char const *host, char const *port);

    TaskInfo Run(const std::string &expression, TaskTypes taskType);

   private:
    void DoConnect();
    void DoSendText(const std::string &expression, TaskTypes taskType);
    void DoSendImage(const std::string &path, TaskTypes taskType);
    void DoRead();

    TaskInfo HandleResponse();

    std::string Host;
    std::string Port;

    net::io_context Ioc;
    tcp::resolver Resolver;
    beast::tcp_stream Stream;
    beast::flat_buffer Buffer;
    http::response<http::string_body> Response;
};

}  // namespace Client
