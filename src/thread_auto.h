#ifndef THREAD_AUTO_H
#define THREAD_AUTO_H

#include <QString>
#include <QThread>
#include <QScriptEngine>
#include <icontrolserver.h>

class ThreadAuto : public QThread {
	Q_OBJECT
public:
	ThreadAuto(IControlServer *pControlServer, QString script);
	~ThreadAuto();

	IControlServer *getControlServer();
	
protected:
	
	void run();
	
private:

	IControlServer *m_pControlServer;
	QString m_sScript;
};

#endif // THREAD_AUTO_H
