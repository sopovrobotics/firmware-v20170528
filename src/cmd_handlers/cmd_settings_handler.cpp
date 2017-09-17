#include "cmd_settings_handler.h"

QString CmdSettingsHandler::cmd(){
	return "settings";
}

void CmdSettingsHandler::handle(QWebSocket *pClient, IControlServer *pControlServer, QJsonObject /*obj*/){
	QJsonObject jsonResponse;
	QJsonObject jsonSettings;
	jsonResponse["cmd"] = QJsonValue(cmd());
	jsonResponse["result"] = "OK";

	ISettings *pSett = pControlServer->settings();
	jsonSettings["port"] = pSett->get_port();
	jsonSettings["servo_pin_comb"] = pSett->get_servo_pin_comb();
	jsonSettings["servo_pin_comb_value_up"] = pSett->get_servo_pin_comb_value_up();
	jsonSettings["servo_pin_comb_value_down"] = pSett->get_servo_pin_comb_value_down();
	
	jsonResponse["data"] = jsonSettings;
	pControlServer->sendMessage(pClient, jsonResponse);
}
