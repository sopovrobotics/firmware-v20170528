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
#include "controlserver.h"
#include "settings.h"

int main(int argc, char** argv) {
	QCoreApplication app(argc, argv);
	Settings *pSett = new Settings();

    QCommandLineParser parser;
    parser.setApplicationDescription("SopovRobotics");
    parser.addHelpOption();


    QCommandLineOption portOption(QStringList() << "p" << "port",
            QCoreApplication::translate("main", ("Port for SopovRobotics [ws default: " + QString::number(pSett->get_port())+ "].").toLatin1()),
            QCoreApplication::translate("main", "port"), QString::number(pSett->get_port()).toLatin1());
    parser.addOption(portOption);
    parser.process(app);
    int port = parser.value(portOption).toInt();

	

    ControlServer *server = new ControlServer(pSett);
    if(server->hasError()){
		return -1;
	}
    
    QObject::connect(server, &ControlServer::closed, &app, &QCoreApplication::quit);
    
	return app.exec();
}
