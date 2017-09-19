#ifndef CONTROLSERVER_H
#define CONTROLSERVER_H

#include <QObject>
#include <QString>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QMap>
#include <QElapsedTimer>
#include <QThread>
#include "interfaces/icmdhandler.h"
#include "interfaces/icontrolserver.h"

// QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
// QT_FORWARD_DECLARE_CLASS(QWebSocket)

class ControlServer : public QObject, public IControlServer {
	
	private:
		Q_OBJECT
	public:
		explicit ControlServer(ISettings *pSett, QObject *parent = Q_NULLPTR);
		~ControlServer();

		virtual void sendMessage(QWebSocket *pClient, QJsonObject obj);
		virtual void sendMessage(QWebSocket *pClient, const QByteArray &data);
		virtual ISettings * settings();
		virtual void turnleft();
		virtual void turnright();
		virtual void forward();
		virtual void backward();
		virtual void stop();
		virtual void comb_up();
		virtual void comb_down();
		
		bool hasError();
				
	Q_SIGNALS:
		void closed();

	private Q_SLOTS:
		void onNewConnection();
		void processTextMessage(QString message);
		void processBinaryMessage(QByteArray message);
		void socketDisconnected();

	private:
		bool m_bHasError;
		void unexportPin(int pin);
		void exportPin(int pin);
		void setPinValue(int pin, int value);
		void directionOutPin(int pin);
		void pwmPin(int pin, int width_signal_usec);
			
		QWebSocketServer *m_pWebSocketServer;
		QList<QWebSocket *> m_clients;
		QMap<QString, ICmdHandler *> m_mapCmdHandlers;
		
		ISettings *m_pSettings;
};

#endif // CONTROLSERVER_H
