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
        : ServerException("don't open the acceptor " + ec.message()) {}
};

class InvalidAcceptorSetOption : public ServerException {
   public:
    explicit InvalidAcceptorSetOption(beast::error_code ec)
        : ServerException("don't set acceptor's reuse option " + ec.message()) {}
};

class InvalidAcceptorBind : public ServerException {
   public:
    explicit InvalidAcceptorBind(beast::error_code ec)
        : ServerException("don't bind to the server address " + ec.message()) {}
};

class InvalidAcceptorListen : public ServerException {
   public:
    explicit InvalidAcceptorListen(beast::error_code ec)
        : ServerException("acceptor don't start listening for connections " + ec.message()) {}
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
    explicit HandlerEmptyRequestBody() : HandlerException("") {}
};

class HandlerWrongRequest : public HandlerException {
   public:
    explicit HandlerWrongRequest() : HandlerException("") {}
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

}  // namespace Tasks
