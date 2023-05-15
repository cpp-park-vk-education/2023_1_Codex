#pragma once

#include <boost/beast/http.hpp>
#include <memory>

#include "ITask.hpp"

namespace Handlers {

namespace http = boost::beast::http;  // from <boost/beast/http.hpp>

class ITaskSearcher {
   public:
    virtual ~ITaskSearcher() {}

    virtual ::Tasks::ITaskUPtr Run(http::request<http::dynamic_body>& request) = 0;
};

using ITaskSearcherUPtr = std::unique_ptr<ITaskSearcher>;

}  // namespace Handlers
