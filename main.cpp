#include <QCoreApplication>
#include <QDebug>
#include <QUrl>
#include "networkmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    qInfo() << "Qt Server Sent Events demo, written by Dylan Van Assche.";
    Network::Manager *manager = Network::Manager::getInstance();
    manager->getResource(QUrl("http://localhost:8888/sncb/events/sse?lastSyncTime=2019-01-20T18:00:00.000Z"));
    return app.exec();
}
