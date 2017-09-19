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
	jsonSettings["secret"] = pSett->get_secret();
	
	jsonSettings["servo_pin_comb"] = pSett->get_servo_pin_comb();
	jsonSettings["servo_pin_comb_value_up"] = pSett->get_servo_pin_comb_value_up();
	jsonSettings["servo_pin_comb_value_down"] = pSett->get_servo_pin_comb_value_down();
	
	jsonSettings["drivers_pin_A1"] = pSett->get_drivers_pin_A1();
	jsonSettings["drivers_pin_A2"] = pSett->get_drivers_pin_A2();
	jsonSettings["drivers_pin_B1"] = pSett->get_drivers_pin_B1();
	jsonSettings["drivers_pin_B2"] = pSett->get_drivers_pin_B2();
	
	jsonSettings["drivers_turnleft_A1"] = pSett->get_drivers_turnleft_A1();
	jsonSettings["drivers_turnleft_A2"] = pSett->get_drivers_turnleft_A2();
	jsonSettings["drivers_turnleft_B1"] = pSett->get_drivers_turnleft_B1();
	jsonSettings["drivers_turnleft_B2"] = pSett->get_drivers_turnleft_B2();
	
	
	jsonSettings["drivers_turnright_A1"] = pSett->get_drivers_turnright_A1();
	jsonSettings["drivers_turnright_A2"] = pSett->get_drivers_turnright_A2();
	jsonSettings["drivers_turnright_B1"] = pSett->get_drivers_turnright_B1();
	jsonSettings["drivers_turnright_B2"] = pSett->get_drivers_turnright_B2();

	jsonSettings["drivers_forward_A1"] = pSett->get_drivers_forward_A1();
	jsonSettings["drivers_forward_A2"] = pSett->get_drivers_forward_A2();
	jsonSettings["drivers_forward_B1"] = pSett->get_drivers_forward_B1();
	jsonSettings["drivers_forward_B2"] = pSett->get_drivers_forward_B2();

	jsonSettings["drivers_backward_A1"] = pSett->get_drivers_backward_A1();
	jsonSettings["drivers_backward_A2"] = pSett->get_drivers_backward_A2();
	jsonSettings["drivers_backward_B1"] = pSett->get_drivers_backward_B1();
	jsonSettings["drivers_backward_B2"] = pSett->get_drivers_backward_B2();
		
	jsonResponse["data"] = jsonSettings;
	pControlServer->sendMessage(pClient, jsonResponse);
}
