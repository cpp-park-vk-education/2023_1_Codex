#include "taskSearcher.hpp"

#include <boost/beast/http.hpp>
#include <memory>
#include <string>

#include "ITask.hpp"
#include "taskInfo.hpp"

namespace Handlers {

TaskSearcher::TaskSearcher(std::shared_ptr<std::string const> docRoot) : DocRoot(std::move(docRoot)) {}

::Tasks::ITaskUPtr TaskSearcher::Run(http::request<http::dynamic_body> &request) {
    ::Tasks::TaskInfo info = DoTaskSearch(request);

    // Create ITaskUPtr using TaskInfo and return it
    // TO DO
}

::Tasks::TaskInfo TaskSearcher::DoTaskSearch(http::request<http::dynamic_body> &request) const {
    // Using Content-Type define type of data and parse it
    // Create TaskInfo struct and return it
    // If emptyData or wrong req -> exception
    // TO DO
}

}  // namespace Handlers
