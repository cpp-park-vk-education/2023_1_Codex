#include <QApplication>
#include <iostream>
#include <memory>

<<<<<<< HEAD
#include "client.hpp"
#include "mainwindow.hpp"
=======
#include "Client.hpp"
#include "MainWindow.hpp"
>>>>>>> origin/dev

int main(int argc, char* argv[]) {
    /* if (argc != 3){
          std::cerr << "Usage: client <host> <port> \n"
              << "Example:\n"
              << "    client www.example.com 80\n";
          return EXIT_FAILURE;
      }
      auto const host = argv[1];
      auto const port = argv[2];
  */
<<<<<<< HEAD
    Client::ClientSPtr client = std::make_shared<Client::Client>("127.0.0.1", "17813");
=======
    Client::ClientSPtr client = std::make_shared<Client::Client>("127.0.0.1", "7273");
>>>>>>> origin/dev
    // Client::ClientSPtr client = std::make_shared<Client::Client>(host, port);

    const char* constArguments[] = {"appname", "-option1", "-option2"};

    QApplication app(argc, const_cast<char**>(constArguments));

    MainWindow w(client);
    // MainWindow w;
    w.show();
    return app.exec();
}
