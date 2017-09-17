#include "cmd_comb_down_handler.h"

QString CmdCombDownHandler::cmd(){
	return "comb_down";
}

void CmdCombDownHandler::handle(QWebSocket */*pClient*/, IControlServer *pControlServer, QJsonObject /*obj*/){
	pControlServer->comb_down();
}
