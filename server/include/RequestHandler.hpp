#pragma once

#include <boost/beast/http.hpp>
#include <memory>
#include <string>

namespace Server {

namespace http = boost::beast::http;  // from <boost/beast/http.hpp>

class RequestHandler {
   public:
    explicit RequestHandler(std::shared_ptr<std::string const> docRoot);

    http::message_generator Run(http::request<http::dynamic_body> &request) const;

   private:
    std::shared_ptr<std::string const> DocRoot;
};

}  // namespace Server
