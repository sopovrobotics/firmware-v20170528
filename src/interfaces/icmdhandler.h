#ifndef INTERFACES_ICMDHANDLER_H
#define INTERFACES_ICMDHANDLER_H

#include <QString>
#include <QJsonObject>
#include "icontrolserver.h"

class ICmdHandler {
	public:
		virtual QString cmd() = 0;
		virtual void handle(QWebSocket *pClient, IControlServer *pControlServer, QJsonObject obj) = 0;
};

#endif // INTERFACES_ICMDHANDLER_H
