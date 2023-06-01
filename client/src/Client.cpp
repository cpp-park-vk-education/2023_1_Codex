#include "Client.hpp"

#include <boost/asio.hpp>
#include <boost/asio/strand.hpp>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

#include "Exceptions.hpp"

namespace Client {

constexpr int HTTP_VERSION = 10;
constexpr int MS_FOR_REPEAT = 1000;

Client::Client(char const *host, char const *port)
    : Host(host),
      Port(port),
      Ioc(net::io_context{}),
      Resolver(net::make_strand(Ioc)),
      Stream(net::make_strand(Ioc)) {}

TaskInfo Client::Run(const std::string &expression, TaskTypes taskType) {
    DoConnect();

    if (*expression.begin() == 'C') {
        DoSendImage(expression, taskType);
    } else {
        DoSendText(expression, taskType);
    }

    DoRead();

    return HandleResponse();
}

void Client::DoConnect() {
    beast::error_code ec;

    // Look up the domain name
    auto results = Resolver.resolve(Host, Port, ec);
    if (ec) {
        unsigned errCount = 1;
        while (ec && errCount < 3) {
            std::this_thread::sleep_for(std::chrono::milliseconds(errCount * MS_FOR_REPEAT));
            ec.clear();

            results = Resolver.resolve(Host, Port, ec);
        }

        // If 3rd trying is fail
        if (ec) {
            throw InvalidResolve(ec);
        }
    }

    Stream.connect(results, ec);
    if (ec) {
        unsigned errCount = 1;
        while (ec && errCount < 3) {
            std::this_thread::sleep_for(std::chrono::milliseconds(errCount * MS_FOR_REPEAT));
            ec.clear();

            Stream.connect(results, ec);
        }

        // If 3rd trying is fail
        if (ec) {
            throw InvalidConnect(ec);
        }
    }
}

void Client::DoSendText(const std::string &expression, TaskTypes taskType) {
    http::request<http::string_body> request;
    request.method(http::verb::post);
    request.target(std::to_string(static_cast<unsigned>(taskType)));
    request.version(HTTP_VERSION);
    request.set(http::field::host, Host);

    request.body() = expression;

    request.set(http::field::content_length, std::to_string(request.body().size()));
    request.set(http::field::content_type, "text/plain");

    http::request_serializer<http::string_body, http::fields> sr{request};

    beast::error_code ec;
    http::write(Stream, sr, ec);

    std::cout << sr.get() << std::endl;

    if (ec) {
        unsigned errCount = 1;
        while (ec && errCount < 3) {
            std::this_thread::sleep_for(std::chrono::milliseconds(errCount * MS_FOR_REPEAT));
            ec.clear();

            http::write(Stream, sr, ec);
        }

        // If 3rd trying is fail
        if (ec) {
            throw InvalidWrite(ec);
        }
    }
}

void Client::DoSendImage(const std::string &path, TaskTypes taskType) {
    std::cout << path << std::endl;
    http::request<http::file_body> request;
    request.method(http::verb::post);
    request.target(std::to_string(static_cast<unsigned>(taskType)));
    request.version(HTTP_VERSION);
    request.set(http::field::host, Host);

    beast::error_code ec;
    http::file_body::value_type body;
    body.open(path.c_str(), beast::file_mode::read, ec);
    if (ec) {
        throw InvalidImageFile(ec);
    }

    request.body() = std::move(body);

    request.set(http::field::content_length, std::to_string(request.body().size()));
    request.set(http::field::content_type, "image/png");

    http::request_serializer<http::file_body, http::fields> sr{request};

    http::write(Stream, sr, ec);
    if (ec) {
        unsigned errCount = 1;
        while (ec && errCount < 3) {
            std::this_thread::sleep_for(std::chrono::milliseconds(errCount * MS_FOR_REPEAT));
            ec.clear();

            http::write(Stream, sr, ec);
        }

        // If 3rd trying is fail
        if (ec) {
            throw InvalidWrite(ec);
        }
    }
}

void Client::DoRead() {
    beast::error_code ec;

    Buffer = {};
    Response = {};

    http::read(Stream, Buffer, Response, ec);
    if (ec) {
        unsigned errCount = 1;
        while (ec && errCount < 3) {
            std::this_thread::sleep_for(std::chrono::milliseconds(errCount * MS_FOR_REPEAT));
            ec.clear();

            http::read(Stream, Buffer, Response, ec);
        }

        // If 3rd trying is fail
        if (ec) {
            throw InvalidRead(ec);
        }
    }

    Stream.socket().shutdown(tcp::socket::shutdown_both, ec);
}

TaskInfo Client::HandleResponse() {
    // Create TaskInfo from Response
    TaskInfo info;

    std::istringstream data(Response.body());
    while (!data.eof()) {
        std::string var;
        getline(data, var, '=');

        if (var == "Type") {
            std::string type;
            getline(data, type);
            info.TaskType = static_cast<TaskTypes>(std::stoi(type));
        } else if (var == "Expression") {
            getline(data, info.TaskData);
        } else if (var == "Answer") {
            getline(data, info.TaskAnswer);
        } else if (var == "Error") {
            getline(data, info.TaskError);
            info.ErrorCode = true;
        }
    }

    std::cout << "Answer: " << info.TaskAnswer << std::endl;
    std::cout << "Error: " << info.TaskError << std::endl;
    return info;
}

}  // namespace Client
