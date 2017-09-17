#include "cmd_turnright_handler.h"

QString CmdTurnrightHandler::cmd(){
	return "turnright";
}

void CmdTurnrightHandler::handle(QWebSocket */*pClient*/, IControlServer *pControlServer, QJsonObject /*obj*/){
	// QJsonObject jsonData;
	// jsonData["cmd"] = QJsonValue(cmd());
	// jsonData["result"] = "OK";
	// pWebSocketServer->sendMessage(pClient, jsonData);
	pControlServer->turnright();
}
