#ifndef CMD_FORWARD_HANDLER_H
#define CMD_FORWARD_HANDLER_H

#include "icmdhandler.h"

#include <QString>
#include <QVariant>

class CmdForwardHandler : public ICmdHandler {
	
	public:
		virtual QString cmd();
		virtual void handle(QWebSocket *pClient, IControlServer *pControlServer, QJsonObject obj);
};

#endif // CMD_FORWARD_HANDLER_H
