#include "cmd_update_settings_handler.h"

QString CmdUpdateSettingsHandler::cmd(){
	return "update_settings";
}

void CmdUpdateSettingsHandler::handle(QWebSocket *pClient, IControlServer *pControlServer, QJsonObject obj1){
	QJsonObject jsonResponse;
	QJsonArray jsonErrors;
	QJsonArray jsonWarnings;
	QJsonObject jsonNewSettings;
	jsonResponse["cmd"] = QJsonValue(cmd());
	
	QJsonObject objNewSettings = obj1["data"].toObject();
	
	ISettings *pSett = pControlServer->settings();
	if(objNewSettings.contains("port")){
		int port = objNewSettings["port"].toInt();
		if(port > 1000 && port < 65536){
			jsonNewSettings["port"] = port;
			pSett->set_port(port);
			jsonWarnings.append("require_reboot");
		}
	}
	
	if(objNewSettings.contains("secret")){
		QString secret = objNewSettings["secret"].toString();
		jsonNewSettings["secret"] = secret;
		pSett->set_secret(secret);
		qDebug() << "secret updated " << secret;
	}
	
	// comb
	
	if(objNewSettings.contains("servo_pin_comb")){
		int pin = objNewSettings["servo_pin_comb"].toString().toInt();
		jsonNewSettings["servo_pin_comb"] = pin;
		pSett->set_servo_pin_comb(pin);
		jsonWarnings.append("require_reboot");
	}
	
	if(objNewSettings.contains("servo_pin_comb_value_up")){
		int val = objNewSettings["servo_pin_comb_value_up"].toString().toInt();
		jsonNewSettings["servo_pin_comb_value_up"] = val;
		pSett->set_servo_pin_comb_value_up(val);
	}
	
	if(objNewSettings.contains("servo_pin_comb_value_down")){
		int val = objNewSettings["servo_pin_comb_value_down"].toString().toInt();
		jsonNewSettings["servo_pin_comb_value_down"] = val;
		pSett->set_servo_pin_comb_value_down(val);
	}

	// Drivers pins
	
	if(objNewSettings.contains("drivers_pin_A1")){
		int pin = objNewSettings["drivers_pin_A1"].toString().toInt();
		jsonNewSettings["drivers_pin_A1"] = pin;
		pSett->set_drivers_pin_A1(pin);
		jsonWarnings.append("require_reboot");
	}
	
	if(objNewSettings.contains("drivers_pin_A2")){
		int pin = objNewSettings["drivers_pin_A2"].toString().toInt();
		jsonNewSettings["drivers_pin_A2"] = pin;
		pSett->set_drivers_pin_A2(pin);
		jsonWarnings.append("require_reboot");
	}
	
	if(objNewSettings.contains("drivers_pin_B1")){
		int pin = objNewSettings["drivers_pin_B1"].toString().toInt();
		jsonNewSettings["drivers_pin_B1"] = pin;
		pSett->set_drivers_pin_B1(pin);
		jsonWarnings.append("require_reboot");
	}
	
	if(objNewSettings.contains("drivers_pin_B2")){
		int pin = objNewSettings["drivers_pin_B2"].toString().toInt();
		jsonNewSettings["drivers_pin_B2"] = pin;
		pSett->set_drivers_pin_B2(pin);
		jsonWarnings.append("require_reboot");
	}

	
	if(jsonWarnings.size() > 0){
		jsonResponse["warnings"] = jsonWarnings;
	}

	if(jsonErrors.size() > 0){
		jsonResponse["errors"] = jsonErrors;
	}

	jsonResponse["data"] = jsonNewSettings;
	pControlServer->sendMessage(pClient, jsonResponse);
}
