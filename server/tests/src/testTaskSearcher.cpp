#include <gtest/gtest.h>

#include <boost/beast/http.hpp>
#include <memory>
#include <string>

#include "ArithmeticTask.hpp"
#include "ITask.hpp"
#include "exceptions.hpp"
#include "taskSearcher.hpp"

const int HTTP_VERSION = 10;

const std::string DOC_ROOT = "/path/to/network";

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
    TaskSearcher taskSearcher(DOC_ROOT);
    Tasks::ITaskUPtr actual = taskSearcher.Run(req);

    ArithmeticTask expected("5 + 10 / 2 - 4 * 7");
    EXPECT_STREQ(expected.GetExpression(), actual.GetExpression());
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
    TaskSearcher taskSearcher(DOC_ROOT);

    EXPECT_THROW(taskSearcher.Run(req), Handlers::HandlerEmptyRequestBody);
}

TEST(TaskSearcherTest, BasicJpgCase) {
    std::string path_to_file = "basicCase.jpg";
    std::ifstream image(path_to_file, std::ios::binary);

    // create req
    http::request<http::dynamic_body> req;
    req.method(http::verb::post);
    req.target("14");
    req.version(HTTP_VERSION);
    req.set(http::field::host, "127.0.0.1");
    req.set(http::field::content_type, "image/jpg");
    beast::ostream(req.body()) << image.rdbuf();
    req.set(http::field::content_length, std::to_string(req.body().size()));

    // test TaskSearcher with current req
    TaskSearcher taskSearcher(DOC_ROOT);
    Tasks::ITaskUPtr actual = taskSearcher.Run(req);

    ArithmeticTask expected("5 + 10 / 2 - 4 * 7");
    EXPECT_STREQ(expected.GetExpression(), actual.GetExpression());
}

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
    TaskSearcher taskSearcher(DOC_ROOT);

    EXPECT_THROW(taskSearcher.Run(req), Handlers::HandlerEmptyRequestBody);
}

TEST(TaskSearcherTest, GetReqCase) {
    // create req
    http::request<http::empty_body> req;
    req.method(http::verb::get);
    req.target("/");
    req.version(HTTP_VERSION);
    req.set(http::field::host, "127.0.0.1");

    // test TaskSearcher with current req
    TaskSearcher taskSearcher(DOC_ROOT);

    EXPECT_THROW(taskSearcher.Run(req), Handlers::HandlerWrongRequest);
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
    TaskSearcher taskSearcher(DOC_ROOT);

    EXPECT_THROW(taskSearcher.Run(req), Handlers::HandlerWrongRequest);
}
