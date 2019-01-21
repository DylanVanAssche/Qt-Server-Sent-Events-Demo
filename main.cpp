/*
 *   This file is part of Qt-SSE-Demo.
 *
 *   Qt-SSE-Demo is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Qt-SSE-Demo is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Qt-SSE-Demo.  If not, see <http://www.gnu.org/licenses/>.
 */
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
