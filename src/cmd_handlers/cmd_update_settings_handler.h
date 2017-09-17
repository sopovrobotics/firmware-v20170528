#ifndef CMD_UPDATE_SETTINGS_HANDLER_H
#define CMD_UPDATE_SETTINGS_HANDLER_H

#include "icmdhandler.h"

#include <QString>
#include <QVariant>

class CmdUpdateSettingsHandler : public ICmdHandler {
	
	public:
		virtual QString cmd();
		virtual void handle(QWebSocket *pClient, IControlServer *pControlServer, QJsonObject obj);
};

#endif // CMD_UPDATE_SETTINGS_HANDLER_H
