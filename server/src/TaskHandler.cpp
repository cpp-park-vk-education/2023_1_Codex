#include "TaskHandler.hpp"

#include "Exceptions.hpp"

namespace Handlers {

namespace beast = boost::beast;  // from <boost/beast.hpp>

TaskHandler::TaskHandler(ITaskSearcherUPtr &&taskSearcher, std::shared_ptr<std::string const> docRoot)
    : TaskSearcher(std::move(taskSearcher)), DocRoot(std::move(docRoot)) {}

http::message_generator TaskHandler::Run(http::request<http::dynamic_body> &request) {
    ::Tasks::ITaskUPtr task;

    // Search task from request
    try {
        task = TaskSearcher.get()->Run(request);
    } catch (const HandlerEmptyRequestBody &ex) {
        using namespace std::string_literals;
        return CreateErrorResponse(request, "Error="s + ex.what());
    } catch (const HandlerInvalidRequest &ex) {
        using namespace std::string_literals;
        return CreateErrorResponse(request, "Error="s + ex.what());
    } catch (const HandlerInvalidFile &ex) {
        return CreateErrorResponse(request, "Error=Don't handle your request because of server error");
    }

    // Send response with solved task
    return CreateResponse(task, request);
}

http::message_generator TaskHandler::CreateResponse(::Tasks::ITaskUPtr &task,
                                                    http::request<http::dynamic_body> &request) const {
    // Solve task. If error, call CreateErrorResponse
    std::string answer;
    try {
        answer = task.get()->Solve();
    } catch (const ::Tasks::TaskException &ex) {
        using namespace std::string_literals;
        std::string msg = "Type="s + std::to_string(task->GetTaskType()) + "\n"s + "Expression="s +
                          task->GetExpression() + "\n"s + "Error="s + ex.what();

        return CreateErrorResponse(request, msg);
    }

    // Using task fill response
    http::response<http::string_body> response{http::status::ok, request.version()};
    response.set(http::field::content_type, "text/plain");

    using namespace std::string_literals;
    response.body() = "Type="s + std::to_string(task->GetTaskType()) + "\n"s + "Expression="s +
                      task->GetExpression() + "\n"s + "Answer="s + answer;

    response.prepare_payload();
    return response;
}

http::message_generator TaskHandler::CreateErrorResponse(http::request<http::dynamic_body> &request,
                                                         const std::string &msg) const {
    // Create response with bad_request status
    http::response<http::string_body> response{http::status::bad_request, request.version()};
    response.set(http::field::content_type, "text/html");
    response.body() = msg;
    response.prepare_payload();
    return response;
}

}  // namespace Handlers
