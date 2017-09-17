#include "cmd_comb_up_handler.h"

QString CmdCombUpHandler::cmd(){
	return "comb_up";
}

void CmdCombUpHandler::handle(QWebSocket */*pClient*/, IControlServer *pControlServer, QJsonObject /*obj*/){
	pControlServer->comb_up();
}
