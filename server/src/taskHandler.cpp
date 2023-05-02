#include "taskHandler.hpp"

#include <boost/beast/http.hpp>
#include <memory>
#include <string>

#include "ITask.hpp"
#include "ITaskSearcher.hpp"
#include "exceptions.hpp"

namespace Handlers {

namespace http = boost::beast::http;  // from <boost/beast/http.hpp>

TaskHandler::TaskHandler(ITaskSearcherUPtr&& taskSearcher, std::shared_ptr<std::string const> docRoot)
    : TaskSearcher(std::move(taskSearcher)), DocRoot(std::move(docRoot)) {}

http::message_generator TaskHandler::Run(http::request<http::dynamic_body>& request) {
    ::Tasks::ITaskUPtr task;

    // TO DO
    try {
        task = TaskSearcher.get()->Run(request);
    } catch (HandlerEmptyRequestBody& ex) {
        // Create errorResponse
    } catch (HandlerWrongRequest& ex) {
        // Create errorResponse
    }

    return CreateResponse(task);
}

http::message_generator TaskHandler::CreateResponse(::Tasks::ITaskUPtr& task) const {
    try {
        std::string answer = task.get()->Solve();
    } catch (::Tasks::TaskException& ex) {
        // Create errorResponse
    }

    http::response<http::string_body> response;
    // Using task fill response
    // TO DO

    return response;
}

}  // namespace Handlers
