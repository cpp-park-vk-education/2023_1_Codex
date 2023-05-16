
#include "mainwindow.h"
#include "client.hpp"
#include <QApplication>
//using namespace Client;
#include<iostream>

int main(int argc, char* argv[]){
    /*if (argc != 3){
        std::cerr << "Usage: client <host> <port> \n"
            << "Example:\n"
            << "    client www.example.com 80\n";
        return EXIT_FAILURE;
    }
    auto const host = argv[1];
    auto const port = argv[2];

Client::Client Client(host, port);*/

    const char* constArguments[] = {"appname", "-option1", "-option2"};

    QApplication app(argc, const_cast<char**>(constArguments));

    //MainWindow w(Client);
    MainWindow w;
    w.show();
    return app.exec();
}
