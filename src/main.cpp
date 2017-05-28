#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <syslog.h>
#include <QtCore>
#include <QFile>
#include <QString>
#include "websocketserver.h"

int main(int argc, char** argv) {
	QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("SopovRobotics");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug", QCoreApplication::translate("main", "Debug output [default: off]."));
    
    parser.addOption(dbgOption);
    QCommandLineOption portOption(QStringList() << "p" << "port",
            QCoreApplication::translate("main", "Port for SopovRobotics ws [default: 1234]."),
            QCoreApplication::translate("main", "port"), QLatin1Literal("1234"));
    parser.addOption(portOption);
    parser.process(app);
    bool debug = parser.isSet(dbgOption);
    int port = parser.value(portOption).toInt();

    WebSocketServer *server = new WebSocketServer(port, debug);
    QObject::connect(server, &WebSocketServer::closed, &app, &QCoreApplication::quit);
    
	return app.exec();
}
