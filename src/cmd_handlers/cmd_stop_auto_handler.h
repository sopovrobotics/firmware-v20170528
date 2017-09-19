#ifndef CMD_STOP_AUTO_HANDLER_H
#define CMD_STOP_AUTO_HANDLER_H

#include "icmdhandler.h"

class CmdStopAutoHandler : public ICmdHandler {
	
	public:
		virtual QString cmd();
		virtual void handle(QWebSocket *pClient, IControlServer *pControlServer, QJsonObject obj);
};

#endif // CMD_STOP_AUTO_HANDLER_H
