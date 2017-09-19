#include "cmd_start_auto_handler.h"

QString CmdStartAutoHandler::cmd(){
	return "start_auto";
}

void CmdStartAutoHandler::handle(QWebSocket *pClient, IControlServer *pControlServer, QJsonObject obj){
	QJsonObject jsonData;
	jsonData["cmd"] = QJsonValue(cmd());
	jsonData["result"] = "OK";
	QString script = "";
	if(obj.contains("script")){
		script = obj["script"].toString();
	}
	pControlServer->sendMessage(pClient, jsonData);
	pControlServer->start_auto(script);
}
