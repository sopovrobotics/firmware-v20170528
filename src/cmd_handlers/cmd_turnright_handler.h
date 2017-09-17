#ifndef CMD_TURNRIGHT_HANDLER_H
#define CMD_TURNRIGHT_HANDLER_H

#include "icmdhandler.h"

#include <QString>
#include <QVariant>

class CmdTurnrightHandler : public ICmdHandler {
	
	public:
		virtual QString cmd();
		virtual void handle(QWebSocket *pClient, IControlServer *pControlServer, QJsonObject obj);
};

#endif // CMD_TURNRIGHT_HANDLER_H
