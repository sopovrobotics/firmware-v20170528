#include "cmd_turnleft_handler.h"

QString CmdTurnleftHandler::cmd(){
	return "turnleft";
}

void CmdTurnleftHandler::handle(QWebSocket */*pClient*/, IControlServer *pControlServer, QJsonObject /*obj*/){
	// QJsonObject jsonData;
	// jsonData["cmd"] = QJsonValue(cmd());
	// jsonData["result"] = "OK";
	// pWebSocketServer->sendMessage(pClient, jsonData);
	pControlServer->turnleft();
}
