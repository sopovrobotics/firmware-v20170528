#include "thread_auto.h"
#include <QFile>
#include <QDir>
#include <QtCore/QDebug>
#include <QCoreApplication>


ThreadAuto::ThreadAuto(IControlServer *pControlServer, QString script)
  : QThread(0) {
	  m_pControlServer = pControlServer;
	  m_sScript = script;
}

// ---------------------------------------------------------------------

ThreadAuto::~ThreadAuto(){
}

// ---------------------------------------------------------------------

IControlServer *ThreadAuto::getControlServer(){
	return m_pControlServer;
}

// ---------------------------------------------------------------------

QScriptValue comb_up_(QScriptContext */*context*/, QScriptEngine *engine) {
	qDebug() << "comb_up_";
	QObject *pThread = engine->globalObject().property("thread").toQObject();
	((ThreadAuto *)pThread)->getControlServer()->comb_up();
    return engine->undefinedValue();
}

// ---------------------------------------------------------------------

QScriptValue comb_down_(QScriptContext */*context*/, QScriptEngine *engine) {
	qDebug() << "comb_down_";
	QObject *pThread = engine->globalObject().property("thread").toQObject();
	((ThreadAuto *)pThread)->getControlServer()->comb_down();
    return engine->undefinedValue();
}

// ---------------------------------------------------------------------

QScriptValue forward_(QScriptContext *context, QScriptEngine *engine) {
	int ms = context->argument(0).toInt32();
	qDebug() << "forward " << ms;
	QObject *pThread = engine->globalObject().property("thread").toQObject();
	((ThreadAuto *)pThread)->getControlServer()->forward();
	QThread::msleep(ms);
	((ThreadAuto *)pThread)->getControlServer()->stop();
    return engine->undefinedValue();
}

// ---------------------------------------------------------------------

QScriptValue backward_(QScriptContext *context, QScriptEngine *engine) {
	int ms = context->argument(0).toInt32();
	qDebug() << "backward " << ms;
	QObject *pThread = engine->globalObject().property("thread").toQObject();
	((ThreadAuto *)pThread)->getControlServer()->backward();
	QThread::msleep(ms);
	((ThreadAuto *)pThread)->getControlServer()->stop();
    return engine->undefinedValue();
}

// ---------------------------------------------------------------------

QScriptValue turnleft_(QScriptContext *context, QScriptEngine *engine) {
	int ms = context->argument(0).toInt32();
	qDebug() << "turnleft " << ms;
	QObject *pThread = engine->globalObject().property("thread").toQObject();
	((ThreadAuto *)pThread)->getControlServer()->turnleft();
	QThread::msleep(ms);
	((ThreadAuto *)pThread)->getControlServer()->stop();
    return engine->undefinedValue();
}

// ---------------------------------------------------------------------

QScriptValue turnright_(QScriptContext *context, QScriptEngine *engine) {
	int ms = context->argument(0).toInt32();
	qDebug() << "turnright " << ms;
	QObject *pThread = engine->globalObject().property("thread").toQObject();
	((ThreadAuto *)pThread)->getControlServer()->turnright();
	QThread::msleep(ms);
	((ThreadAuto *)pThread)->getControlServer()->stop();
    return engine->undefinedValue();
}

// ---------------------------------------------------------------------

void ThreadAuto::run(){
	 
	QScriptEngine engine;

	engine.globalObject().setProperty("thread", engine.newQObject((QObject *)this));

	engine.globalObject().setProperty("comb_up", engine.newFunction(comb_up_));
	engine.globalObject().setProperty("comb_down", engine.newFunction(comb_down_));
	
	engine.globalObject().setProperty("forward", engine.newFunction(forward_));
	engine.globalObject().setProperty("backward", engine.newFunction(backward_));
	engine.globalObject().setProperty("turnleft", engine.newFunction(turnleft_));
	engine.globalObject().setProperty("turnright", engine.newFunction(turnright_));
	
	// engine.globalObject().setProperty("console.log", engine.newFunction(let2_, turnleftProto));
	
	qDebug() << "evaluate";
	QScriptValue result = engine.evaluate(m_sScript, "autocontrol.js");
	
	if(!engine.hasUncaughtException()){
		qDebug() << engine.uncaughtException().toString();
	}
	
	engine.collectGarbage();
	QThread::usleep(200000);
	
}

// ---------------------------------------------------------------------
