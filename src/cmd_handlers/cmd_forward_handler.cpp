#include "cmd_forward_handler.h"

QString CmdForwardHandler::cmd(){
	return "forward";
}

void CmdForwardHandler::handle(QWebSocket */*pClient*/, IControlServer *pControlServer, QJsonObject /*obj*/){
	pControlServer->forward();
}
