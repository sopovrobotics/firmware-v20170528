#ifndef CMD_STOP_HANDLER_H
#define CMD_STOP_HANDLER_H

#include "icmdhandler.h"

#include <QString>
#include <QVariant>

class CmdStopHandler : public ICmdHandler {
	
	public:
		virtual QString cmd();
		virtual void handle(QWebSocket *pClient, IControlServer *pControlServer, QJsonObject obj);
};

#endif // CMD_STOP_HANDLER_H
