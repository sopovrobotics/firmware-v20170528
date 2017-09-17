#ifndef CMD_TURNLEFT_HANDLER_H
#define CMD_TURNLEFT_HANDLER_H

#include "icmdhandler.h"

#include <QString>
#include <QVariant>

class CmdTurnleftHandler : public ICmdHandler {
	
	public:
		virtual QString cmd();
		virtual void handle(QWebSocket *pClient, IControlServer *pControlServer, QJsonObject obj);
};

#endif // CMD_TURNLEFT_HANDLER_H
