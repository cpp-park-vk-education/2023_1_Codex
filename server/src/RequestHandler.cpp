#include "RequestHandler.hpp"

#include <boost/beast/http.hpp>
#include <memory>
#include <string>

#include "TaskHandler.hpp"
#include "TaskSearcher.hpp"

namespace Server {

namespace http = boost::beast::http;  // from <boost/beast/http.hpp>

RequestHandler::RequestHandler(std::shared_ptr<std::string const> docRoot) : DocRoot(std::move(docRoot)) {}

http::message_generator RequestHandler::Run(http::request<http::dynamic_body> &request) const {
    // There is only one path for handling request in our program
    auto taskSearcher = std::make_unique<::Handlers::TaskSearcher>(DocRoot);
    ::Handlers::TaskHandler taskHandler(std::move(taskSearcher), DocRoot);

    return taskHandler.Run(request);
}

}  // namespace Server
