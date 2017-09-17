#ifndef CMD_SETTINGS_HANDLER_H
#define CMD_SETTINGS_HANDLER_H

#include "icmdhandler.h"

#include <QString>
#include <QVariant>

class CmdSettingsHandler : public ICmdHandler {
	
	public:
		virtual QString cmd();
		virtual void handle(QWebSocket *pClient, IControlServer *pControlServer, QJsonObject obj);
};

#endif // CMD_SETTINGS_HANDLER_H
