#include <QCoreApplication>
#include <QDebug>
#include <QUrl>
#include "networkmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    qInfo() << "Qt Server Sent Events demo, written by Dylan Van Assche.";

    // Construct a Network::Manager instance
    Network::Manager *manager = Network::Manager::getInstance();

    if(argc == 2) {
        // Connect to the resource given by argv[1]
        manager->getResource(QUrl(argv[1]));
    }
    else {
        qInfo() << "USAGE: ./qt-sse-demo URL";
        app.exit();
    }

    return app.exec();
}
