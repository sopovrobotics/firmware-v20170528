#include "cmd_stop_handler.h"

QString CmdStopHandler::cmd(){
	return "stop";
}

void CmdStopHandler::handle(QWebSocket */*pClient*/, IControlServer *pControlServer, QJsonObject /*obj*/){
	pControlServer->stop();
}
