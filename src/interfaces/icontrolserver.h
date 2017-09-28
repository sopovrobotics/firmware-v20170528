#ifndef INTERFACES_ICONTROLSERVER_H
#define INTERFACES_ICONTROLSERVER_H

#include <QJsonObject>
#include <QWebSocket>
#include "isettings.h"

class IControlServer {
	public:
		virtual void sendMessage(QWebSocket *pClient, QJsonObject obj) = 0;
		virtual void sendMessage(QWebSocket *pClient, const QByteArray &data) = 0;
		virtual ISettings * settings() = 0;
		virtual void turnleft() = 0;
		virtual void turnright() = 0;
		virtual void forward() = 0;
		virtual void backward() = 0;
		virtual void stop() = 0;
		virtual void comb_up() = 0;
		virtual void comb_down() = 0;
		virtual void start_auto(QString script) = 0;
		virtual void stop_auto() = 0;
		virtual void send_auto_stopped() = 0;
};

#endif // INTERFACES_ICONTROLSERVER_H
