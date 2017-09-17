#include "cmd_backward_handler.h"

QString CmdBackwardHandler::cmd(){
	return "backward";
}

void CmdBackwardHandler::handle(QWebSocket */*pClient*/, IControlServer *pControlServer, QJsonObject /*obj*/){
	// QJsonObject jsonData;
	// jsonData["cmd"] = QJsonValue(cmd());
	// jsonData["result"] = "OK";
	// pWebSocketServer->sendMessage(pClient, jsonData);
	pControlServer->backward();
}
