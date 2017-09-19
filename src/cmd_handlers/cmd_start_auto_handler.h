#ifndef CMD_START_AUTO_HANDLER_H
#define CMD_START_AUTO_HANDLER_H

#include "icmdhandler.h"

class CmdStartAutoHandler : public ICmdHandler {
	
	public:
		virtual QString cmd();
		virtual void handle(QWebSocket *pClient, IControlServer *pControlServer, QJsonObject obj);
};

#endif // CMD_START_AUTO_HANDLER_H
