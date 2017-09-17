#ifndef CMD_COMB_DOWN_HANDLER_H
#define CMD_COMB_DOWN_HANDLER_H

#include "icmdhandler.h"

#include <QString>
#include <QVariant>

class CmdCombDownHandler : public ICmdHandler {
	
	public:
		virtual QString cmd();
		virtual void handle(QWebSocket *pClient, IControlServer *pControlServer, QJsonObject obj);
};

#endif // CMD_COMB_DOWN_HANDLER_H
