#pragma once

#include <exception>
#include <memory>
#include <string>

#include "boost/beast/core.hpp"

namespace Server {

namespace beast = boost::beast;  // from <boost/beast.hpp>

class ServerException : public std::exception {
   public:
    explicit ServerException(std::string msg) : Msg(std::move(msg)) {}

    const char *what() const noexcept override {
        return Msg.c_str();
    }

   private:
    std::string Msg;
};

class InvalidAcceptorOpen : public ServerException {
   public:
    explicit InvalidAcceptorOpen(beast::error_code ec)
        : ServerException("Don't open the acceptor " + ec.message()) {}
};

class InvalidAcceptorSetOption : public ServerException {
   public:
    explicit InvalidAcceptorSetOption(beast::error_code ec)
        : ServerException("Don't set acceptor's reuse option " + ec.message()) {}
};

class InvalidAcceptorBind : public ServerException {
   public:
    explicit InvalidAcceptorBind(beast::error_code ec)
        : ServerException("Don't bind to the server address " + ec.message()) {}
};

class InvalidAcceptorListen : public ServerException {
   public:
    explicit InvalidAcceptorListen(beast::error_code ec)
        : ServerException("Acceptor don't start listening for connections " + ec.message()) {}
};

}  // namespace Server

namespace Handlers {

class HandlerException : public std::exception {
   public:
    explicit HandlerException(std::string msg) : Msg(std::move(msg)) {}

    const char *what() const noexcept override {
        return Msg.c_str();
    }

   private:
    std::string Msg;
};

class HandlerEmptyRequestBody : public HandlerException {
   public:
    explicit HandlerEmptyRequestBody() : HandlerException("Empty body of request") {}
};

class HandlerInvalidRequest : public HandlerException {
   public:
    explicit HandlerInvalidRequest(std::string &msg)
        : HandlerException("Wrong request because of invalid" + msg) {}
};

}  // namespace Handlers

namespace Tasks {

class TaskException : public std::exception {
   public:
    explicit TaskException(std::string msg) : Msg(std::move(msg)) {}

    const char *what() const noexcept override {
        return Msg.c_str();
    }

   private:
    std::string Msg;
};

class TaskInvalidData : public TaskException {
   public:
    explicit TaskInvalidData(std::string &msg) : TaskException(msg) {}
};

}  // namespace Tasks
