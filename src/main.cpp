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

    QCommandLineOption portOption(QStringList() << "p" << "port",
            QCoreApplication::translate("main", "Port for SopovRobotics ws [default: 7528]."),
            QCoreApplication::translate("main", "port"), QLatin1Literal("7528"));
    parser.addOption(portOption);
    parser.process(app);
    int port = parser.value(portOption).toInt();

    WebSocketServer *server = new WebSocketServer(port);
    if(server->hasError()){
		return -1;
	}
    
    QObject::connect(server, &WebSocketServer::closed, &app, &QCoreApplication::quit);
    
	return app.exec();
}
