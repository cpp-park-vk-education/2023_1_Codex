#include "session.hpp"

#include <boost/asio/dispatch.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <chrono>
#include <memory>
#include <string>
#include <thread>

#include "exceptions.hpp"
#include "requestHandler.hpp"

namespace Server {

namespace beast = boost::beast;       // from <boost/beast.hpp>
namespace http = boost::beast::http;  // from <boost/beast/http.hpp>
namespace net = boost::asio;          // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;     // from <boost/asio/ip/tcp.hpp>

constexpr int MS_FOR_REPEAT = 1000;

Session::Session(tcp::socket &&socket, std::shared_ptr<std::string const> docRoot)
    : Stream(std::move(socket)), Handler({docRoot}), DocRoot(std::move(docRoot)) {}

void Session::Run() {
    // We need to be executing within a strand to perform async operations
    // on the I/O objects in this session. Although not strictly necessary
    // for single-threaded contexts, this example code is written to be
    // thread-safe by default.
    auto self(shared_from_this());
    net::dispatch(Stream.get_executor(), [this, self]() { DoRead(); });
}

void Session::DoRead() {
    // Make the request empty before reading,
    // otherwise the operation behavior is undefined.
    Request = {};

    Stream.expires_after(std::chrono::seconds(30));

    auto self(shared_from_this());
    http::async_read(Stream, Buffer, Request,
                     [this, self](beast::error_code ec, std::size_t bytes_transferred) {
                         CheckRead(ec, bytes_transferred);
                     });
}

void Session::CheckRead(beast::error_code ec, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    // If any error including http::error::end_of_stream
    if (ec) {
        DoClose();
    }

    DoWrite();
}

void Session::DoWrite() {
    http::message_generator response = Handler.Run(Request);

    auto self(shared_from_this());
    beast::async_write(Stream, std::move(response),
                       [this, self](beast::error_code ec, std::size_t bytes_transferred) {
                           CheckWrite(ec, bytes_transferred);
                       });
}

void Session::CheckWrite(beast::error_code ec, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    // Anyway after write(fail or success)
    DoClose();
}

void Session::DoClose() {
    beast::error_code ec;
    Stream.socket().shutdown(tcp::socket::shutdown_send, ec);

    // At this point the connection is closed gracefully
}

}  // namespace Server
