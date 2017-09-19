#include "cmd_stop_auto_handler.h"

QString CmdStopAutoHandler::cmd(){
	return "stop_auto";
}

void CmdStopAutoHandler::handle(QWebSocket *pClient, IControlServer *pControlServer, QJsonObject /*obj*/){
	QJsonObject jsonData;
	jsonData["cmd"] = QJsonValue(cmd());
	jsonData["result"] = "OK";
	pControlServer->sendMessage(pClient, jsonData);
	pControlServer->stop_auto();
}
