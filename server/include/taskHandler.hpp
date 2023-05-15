#pragma once

#include <boost/beast/http.hpp>
#include <memory>
#include <string>

#include "IHandler.hpp"
#include "ITask.hpp"
#include "ITaskSearcher.hpp"

namespace Handlers {

namespace http = boost::beast::http;  // from <boost/beast/http.hpp>

class TaskHandler final : public IHandler {
   public:
    TaskHandler(ITaskSearcherUPtr &&taskSearcher, std::shared_ptr<std::string const> docRoot);
    http::message_generator Run(http::request<http::dynamic_body> &request) override;

   private:
    http::message_generator CreateResponse(::Tasks::ITaskUPtr &task) const;

    ITaskSearcherUPtr TaskSearcher;
    std::shared_ptr<std::string const> DocRoot;
};

}  // namespace Handlers
