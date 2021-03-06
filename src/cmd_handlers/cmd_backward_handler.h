#ifndef CMD_BACKWARD_HANDLER_H
#define CMD_BACKWARD_HANDLER_H

#include "icmdhandler.h"

#include <QString>
#include <QVariant>

class CmdBackwardHandler : public ICmdHandler {
	
	public:
		virtual QString cmd();
		virtual void handle(QWebSocket *pClient, IControlServer *pControlServer, QJsonObject obj);
};

#endif // CMD_BACKWARD_HANDLER_H
