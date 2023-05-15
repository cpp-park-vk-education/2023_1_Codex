#pragma once

#include <boost/beast/http.hpp>
#include <memory>

namespace Handlers {

namespace http = boost::beast::http;  // from <boost/beast/http.hpp>

class IHandler {
   public:
    virtual ~IHandler() {}

    virtual http::message_generator Run(http::request<http::dynamic_body> &request) = 0;
};

using IHandlerUPtr = std::unique_ptr<IHandler>;

}  // namespace Handlers
