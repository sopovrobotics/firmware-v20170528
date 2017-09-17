#ifndef CMD_COMB_UP_HANDLER_H
#define CMD_COMB_UP_HANDLER_H

#include "icmdhandler.h"

#include <QString>
#include <QVariant>

class CmdCombUpHandler : public ICmdHandler {
	
	public:
		virtual QString cmd();
		virtual void handle(QWebSocket *pClient, IControlServer *pControlServer, QJsonObject obj);
};

#endif // CMD_COMB_UP_HANDLER_H
