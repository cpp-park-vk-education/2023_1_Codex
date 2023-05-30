#include <QApplication>
#include <iostream>
#include <memory>

#include "Client.hpp"
#include "MainWindow.hpp"

int main(int argc, char *argv[]) {
    // if (argc != 3) {
    //     std::cerr << "Usage: client <host> <port> \n"
    //               << "Example:\n"
    //               << "    client www.example.com 80\n";
    //     return EXIT_FAILURE;
    // }
    // auto const host = argv[1];
    // auto const port = argv[2];

    auto const host = "127.0.0.1";
    auto const port = "7273";

    Client::ClientSPtr client = std::make_shared<Client::Client>(host, port);

    const char *constArguments[] = {"appname", "-option1", "-option2"};
    QApplication app(argc, const_cast<char **>(constArguments));

    MainWindow w(client);
    // MainWindow w;
    w.show();
    return app.exec();
}
