#include "Session.hpp"

#include <boost/asio/dispatch.hpp>
#include <chrono>

#include "SessionManager.hpp"

namespace Server {

namespace net = boost::asio;  // from <boost/asio.hpp>

Session::Session(tcp::socket&& socket, SessionManager& manager, std::shared_ptr<std::string const> docRoot)
    : Stream(std::move(socket)), Handler({docRoot}), Manager(manager), DocRoot(std::move(docRoot)) {}

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
    Buffer = {};
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
        Manager.DoClose(shared_from_this());
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
    Manager.DoClose(shared_from_this());
}

void Session::DoClose() {
    beast::error_code ec;
    Stream.socket().shutdown(tcp::socket::shutdown_both, ec);

    // At this point the connection is closed gracefully
}

}  // namespace Server
