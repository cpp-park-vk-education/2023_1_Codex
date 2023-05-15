#pragma once

#include <boost/beast/http.hpp>
#include <memory>
#include <string>

#include "ITask.hpp"
#include "ITaskSearcher.hpp"
#include "taskInfo.hpp"

namespace Handlers {

namespace http = boost::beast::http;  // from <boost/beast/http.hpp>

class TaskSearcher final : public ITaskSearcher {
   public:
    explicit TaskSearcher(std::shared_ptr<std::string const> docRoot);

    ::Tasks::ITaskUPtr Run(http::request<http::dynamic_body> &request) override;

   private:
    ::Tasks::TaskInfo DoTaskSearch(http::request<http::dynamic_body> &request) const;

    std::shared_ptr<std::string const> DocRoot;
};

}  // namespace Handlers
