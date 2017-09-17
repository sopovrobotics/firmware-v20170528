#include "cmd_update_settings_handler.h"

QString CmdUpdateSettingsHandler::cmd(){
	return "update_settings";
}

void CmdUpdateSettingsHandler::handle(QWebSocket */*pClient*/, IControlServer *pControlServer, QJsonObject /*obj*/){
	/*QJsonObject jsonResponse;
	QJsonObject jsonSettings;
	jsonResponse["cmd"] = QJsonValue(cmd());
	jsonResponse["result"] = "OK";
	
	
	ISettings *pSett = pControlServer->settings();
	jsonSettings['port'] = pSett->port();
	
	
	jsonData["data"] = jsonSettings;
	pControlServer->sendMessage(pClient, jsonResponse);*/
}
