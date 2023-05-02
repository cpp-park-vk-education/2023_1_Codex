#pragma once

#include <exception>
#include <memory>
#include <string>

#include "boost/beast/core.hpp"

namespace Client {

namespace beast = boost::beast;  // from <boost/beast.hpp>

class ClientException : public std::exception {
   public:
    explicit ClientException(std::string msg) : Msg(std::move(msg)) {}

    const char *what() const noexcept override {
        return Msg.c_str();
    }

   private:
    std::string Msg;
};

class InvalidResolve : public ClientException {
   public:
    explicit InvalidResolve(beast::error_code ec)
        : ClientException("don't resolve IP address " + ec.message()) {}
};

class InvalidConnect : public ClientException {
   public:
    explicit InvalidConnect(beast::error_code ec)
        : ClientException("don't connect to IP address " + ec.message()) {}
};

class InvalidWrite : public ClientException {
   public:
    explicit InvalidWrite(beast::error_code ec) : ClientException("don't write to stream " + ec.message()) {}
};

class InvalidImageFile : public ClientException {
   public:
    explicit InvalidImageFile(beast::error_code ec)
        : ClientException("don't open file with image " + ec.message()) {}
};

class InvalidRead : public ClientException {
   public:
    explicit InvalidRead(beast::error_code ec)
        : ClientException("\"don't read from stream " + ec.message()) {}
};

}  // namespace Client
