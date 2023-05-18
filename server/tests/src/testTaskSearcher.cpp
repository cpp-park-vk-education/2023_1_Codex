#include <gtest/gtest.h>

#include <boost/beast/http.hpp>
#include <fstream>
#include <memory>
#include <string>

#include "Exceptions.hpp"
#include "ITask.hpp"
#include "TaskInfo.hpp"
#include "TaskSearcher.hpp"
#include "arithmeticTask.hpp"

namespace Tests {

const int HTTP_VERSION = 10;

auto const DOC_ROOT = std::make_shared<std::string>("/path/to/network");

namespace beast = boost::beast;       // from <boost/beast.hpp>
namespace http = boost::beast::http;  // from <boost/beast/http.hpp>

TEST(TaskSearcherTest, BasicStrCase) {
    // create req
    http::request<http::dynamic_body> req;
    req.method(http::verb::post);
    req.target("14");
    req.version(HTTP_VERSION);
    req.set(http::field::host, "127.0.0.1");
    req.set(http::field::content_type, "text/plain");
    beast::ostream(req.body()) << "5 + 10 / 2 - 4 * 7";
    req.set(http::field::content_length, std::to_string(req.body().size()));

    // test TaskSearcher with current req
    ::Handlers::TaskSearcher taskSearcher(DOC_ROOT);
    ::Tasks::ITaskUPtr actual = taskSearcher.Run(req);

    ::Tasks::ArithmeticTask expected("5 + 10 / 2 - 4 * 7", ::Tasks::TaskTypes::Arithmetic);
    EXPECT_STREQ(expected.GetExpression().c_str(), actual.get()->GetExpression().c_str());
    EXPECT_EQ(expected.GetTaskType(), actual.get()->GetTaskType());
}

TEST(TaskSearcherTest, EmptyStrCase) {
    // create req
    http::request<http::dynamic_body> req;
    req.method(http::verb::post);
    req.target("14");
    req.version(HTTP_VERSION);
    req.set(http::field::host, "127.0.0.1");
    req.set(http::field::content_type, "text/plain");
    beast::ostream(req.body()) << "";
    req.set(http::field::content_length, std::to_string(req.body().size()));

    // test TaskSearcher with current req
    ::Handlers::TaskSearcher taskSearcher(DOC_ROOT);

    EXPECT_THROW(taskSearcher.Run(req), ::Handlers::HandlerEmptyRequestBody);
}

// Text recognizer isn't implement
// TEST(TaskSearcherTest, BasicJpgCase) {
//     std::string path_to_file = "basicCase.jpg";
//     std::ifstream image(path_to_file, std::ios::binary);
//
//     // create req
//     http::request<http::dynamic_body> req;
//     req.method(http::verb::post);
//     req.target("14");
//     req.version(HTTP_VERSION);
//     req.set(http::field::host, "127.0.0.1");
//     req.set(http::field::content_type, "image.jpg");
//     beast::ostream(req.body()) << image.rdbuf();
//     req.set(http::field::content_length, std::to_string(req.body().size()));
//
//     // test TaskSearcher with current req
//     ::Handlers::TaskSearcher taskSearcher(DOC_ROOT);
//     ::Tasks::ITaskUPtr actual = taskSearcher.Run(req);
//
//     ::Tasks::ArithmeticTask expected("5 + 10 / 2 - 4 * 7", ::Tasks::TaskTypes::Arithmetic);
//     EXPECT_STREQ(expected.GetExpression().c_str(), actual.get()->GetExpression().c_str());
//     EXPECT_EQ(expected.GetTaskType(), actual.get()->GetTaskType());
// }

TEST(TaskSearcherTest, EmptyJpgCase) {
    // create req
    http::request<http::dynamic_body> req;
    req.method(http::verb::post);
    req.target("14");
    req.version(HTTP_VERSION);
    req.set(http::field::host, "127.0.0.1");
    req.set(http::field::content_type, "image/jpg");
    beast::ostream(req.body()) << "";
    req.set(http::field::content_length, std::to_string(req.body().size()));

    // test TaskSearcher with current req
    ::Handlers::TaskSearcher taskSearcher(DOC_ROOT);

    EXPECT_THROW(taskSearcher.Run(req), ::Handlers::HandlerEmptyRequestBody);
}

TEST(TaskSearcherTest, GetReqCase) {
    // create req
    http::request<http::dynamic_body> req;
    req.method(http::verb::get);
    req.target("/");
    req.version(HTTP_VERSION);
    req.set(http::field::host, "127.0.0.1");

    // test TaskSearcher with current req
    ::Handlers::TaskSearcher taskSearcher(DOC_ROOT);

    EXPECT_THROW(taskSearcher.Run(req), ::Handlers::HandlerInvalidRequest);
}

TEST(TaskSearcherTest, WrongContentTypeCase) {
    // create req
    http::request<http::dynamic_body> req;
    req.method(http::verb::post);
    req.target("14");
    req.version(HTTP_VERSION);
    req.set(http::field::host, "127.0.0.1");
    req.set(http::field::content_type, "text/html");
    beast::ostream(req.body()) << "<span class=\"task\">5 + 10 /&nbsp; 2 - 4 * 7</span>";
    req.set(http::field::content_length, std::to_string(req.body().size()));

    // test TaskSearcher with current req
    ::Handlers::TaskSearcher taskSearcher(DOC_ROOT);

    EXPECT_THROW(taskSearcher.Run(req), ::Handlers::HandlerInvalidRequest);
}

}  // namespace Tests
