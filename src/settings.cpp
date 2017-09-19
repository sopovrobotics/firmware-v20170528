#include "settings.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
#include <QHostAddress>
#include "cmd_handlers/create_cmd_handlers.h"
#include <QProcess>
#include <QFile>
// QT_USE_NAMESPACE

// ---------------------------------------------------------------------

Settings::Settings() {
	m_sFilename = "/etc/sopovrobotics/settings_20170528.ini";
	this->load();
	this->save();
}

// ---------------------------------------------------------------------

int Settings::readIntFromSettings(QSettings &sett, QString settName, int defaultValue){
	int nResult = defaultValue;
	if(sett.contains(settName)){
		nResult = sett.value(settName, nResult).toInt();
	}else{
		qDebug() << "[WARNING] " << settName << " - not found in " << m_sFilename << "\n\t Will be used default value: " << defaultValue;
	}
	return nResult;
}

// ---------------------------------------------------------------------

QString Settings::readStringFromSettings(QSettings &sett, QString settName, QString defaultValue){
	QString sResult = defaultValue;
	if(sett.contains(settName)){
		sResult = sett.value(settName, sResult).toString();
	}else{
		qDebug() << "[WARNING] " << settName << " - not found in " << m_sFilename << "\n\t Will be used default value: " << defaultValue;
	}
	return sResult;
}

// ---------------------------------------------------------------------

QStringList Settings::readStringListFromSettings(QSettings &sett, QString settName, QStringList defaultValue){
	QStringList sResult = defaultValue;
	if(sett.contains(settName)){
		sResult = sett.value(settName, sResult).toStringList();
	}else{
		qDebug() << "[WARNING] " << settName << " - not found in " << m_sFilename << "\n\t Will be used default value: " << defaultValue;
	}
	return sResult;
}

// ---------------------------------------------------------------------

bool Settings::readBooleanFromSettings(QSettings &sett, QString settName, bool defaultValue){
	bool bResult = defaultValue;
	if(sett.contains(settName)){
		bResult = sett.value(settName, bResult).toBool();
	}else{
		qDebug() << "[WARNING] " << settName << " - not found in " << m_sFilename << "\n\t Will be used default value: " << defaultValue;
	}
	return bResult;
}

// ---------------------------------------------------------------------

bool Settings::load(){
	
	// dafault
	m_nPort = 7528;
	m_sSecret = "";
	
	m_nServo_PinComb = 7;
	m_nServo_PinComb_value_up = 700;
	m_nServo_PinComb_value_down = 1200;
	
	m_nDrivers_PIN_A1 = 12;
	m_nDrivers_PIN_A2 = 11;
	m_nDrivers_PIN_B1 = 3;
	m_nDrivers_PIN_B2 = 6;
	
	m_nDrivers_turnleft_A1 = 0;
	m_nDrivers_turnleft_A2 = 1;
	m_nDrivers_turnleft_B1 = 0;
	m_nDrivers_turnleft_B2 = 1;
	
	m_nDrivers_turnright_A1 = 1;
	m_nDrivers_turnright_A2 = 0;
	m_nDrivers_turnright_B1 = 1;
	m_nDrivers_turnright_B2 = 0;

	m_nDrivers_forward_A1 = 1;
	m_nDrivers_forward_A2 = 0;
	m_nDrivers_forward_B1 = 0;
	m_nDrivers_forward_B2 = 1;
	
	m_nDrivers_backward_A1 = 0;
	m_nDrivers_backward_A2 = 1;
	m_nDrivers_backward_B1 = 1;
	m_nDrivers_backward_B2 = 0;
	
	if(QFile::exists(m_sFilename)){
		QSettings sett(m_sFilename, QSettings::IniFormat);

		m_nPort = readIntFromSettings(sett, "MAIN/port", m_nPort);
		m_sSecret = readStringFromSettings(sett, "MAIN/secret", m_sSecret);
	
		m_nServo_PinComb = readIntFromSettings(sett, "SERVO/pin_comb", m_nServo_PinComb);
		m_nServo_PinComb_value_up = readIntFromSettings(sett, "SERVO/pin_comb_value_up", m_nServo_PinComb_value_up);
		m_nServo_PinComb_value_down = readIntFromSettings(sett, "SERVO/pin_comb_value_down", m_nServo_PinComb_value_down);
		
		m_nDrivers_PIN_A1 = readIntFromSettings(sett, "DRIVERS/PIN_A1", m_nDrivers_PIN_A1);
		m_nDrivers_PIN_A2 = readIntFromSettings(sett, "DRIVERS/PIN_A2", m_nDrivers_PIN_A2);
		m_nDrivers_PIN_B1 = readIntFromSettings(sett, "DRIVERS/PIN_B1", m_nDrivers_PIN_B1);
		m_nDrivers_PIN_B2 = readIntFromSettings(sett, "DRIVERS/PIN_B2", m_nDrivers_PIN_B2);
	
		m_nDrivers_turnleft_A1 = readIntFromSettings(sett, "DRIVERS/turnleft_A1", m_nDrivers_turnleft_A1);
		m_nDrivers_turnleft_A2 = readIntFromSettings(sett, "DRIVERS/turnleft_A2", m_nDrivers_turnleft_A2);
		m_nDrivers_turnleft_B1 = readIntFromSettings(sett, "DRIVERS/turnleft_B1", m_nDrivers_turnleft_B1);
		m_nDrivers_turnleft_B2 = readIntFromSettings(sett, "DRIVERS/turnleft_B2", m_nDrivers_turnleft_B2);

		m_nDrivers_turnright_A1 = readIntFromSettings(sett, "DRIVERS/turnright_A1", m_nDrivers_turnright_A1);
		m_nDrivers_turnright_A2 = readIntFromSettings(sett, "DRIVERS/turnright_A2", m_nDrivers_turnright_A2);
		m_nDrivers_turnright_B1 = readIntFromSettings(sett, "DRIVERS/turnright_B1", m_nDrivers_turnright_B1);
		m_nDrivers_turnright_B2 = readIntFromSettings(sett, "DRIVERS/turnright_B2", m_nDrivers_turnright_B2);

		m_nDrivers_forward_A1 = readIntFromSettings(sett, "DRIVERS/forward_A1", m_nDrivers_forward_A1);
		m_nDrivers_forward_A2 = readIntFromSettings(sett, "DRIVERS/forward_A2", m_nDrivers_forward_A2);
		m_nDrivers_forward_B1 = readIntFromSettings(sett, "DRIVERS/forward_B1", m_nDrivers_forward_B1);
		m_nDrivers_forward_B2 = readIntFromSettings(sett, "DRIVERS/forward_B2", m_nDrivers_forward_B2);

		m_nDrivers_backward_A1 = readIntFromSettings(sett, "DRIVERS/backward_A1", m_nDrivers_backward_A1);
		m_nDrivers_backward_A2 = readIntFromSettings(sett, "DRIVERS/backward_A2", m_nDrivers_backward_A2);
		m_nDrivers_backward_B1 = readIntFromSettings(sett, "DRIVERS/backward_B1", m_nDrivers_backward_B1);
		m_nDrivers_backward_B2 = readIntFromSettings(sett, "DRIVERS/backward_B2", m_nDrivers_backward_B2);
		
		return true;
	}
	
	
	return false;
}

// ---------------------------------------------------------------------

bool Settings::save(){
	QSettings sett(m_sFilename, QSettings::IniFormat);

	if(!sett.isWritable()){ // TODO fix if file not exists
		return false;
	}
	
	sett.setValue("MAIN/port", m_nPort);
	sett.setValue("MAIN/secret", m_sSecret);
	
	sett.setValue("SERVO/pin_comb", m_nServo_PinComb);
	sett.setValue("SERVO/pin_comb_value_up", m_nServo_PinComb_value_up);
	sett.setValue("SERVO/pin_comb_value_down", m_nServo_PinComb_value_down);

	sett.setValue("DRIVERS/PIN_A1", m_nDrivers_PIN_A1);
	sett.setValue("DRIVERS/PIN_A2", m_nDrivers_PIN_A2);
	sett.setValue("DRIVERS/PIN_B1", m_nDrivers_PIN_B1);
	sett.setValue("DRIVERS/PIN_B2", m_nDrivers_PIN_B2);
	
	sett.setValue("DRIVERS/turnleft_A1", m_nDrivers_turnleft_A1);
	sett.setValue("DRIVERS/turnleft_A2", m_nDrivers_turnleft_A2);
	sett.setValue("DRIVERS/turnleft_B1", m_nDrivers_turnleft_B1);
	sett.setValue("DRIVERS/turnleft_B2", m_nDrivers_turnleft_B2);

	sett.setValue("DRIVERS/turnright_A1", m_nDrivers_turnright_A1);
	sett.setValue("DRIVERS/turnright_A2", m_nDrivers_turnright_A2);
	sett.setValue("DRIVERS/turnright_B1", m_nDrivers_turnright_B1);
	sett.setValue("DRIVERS/turnright_B2", m_nDrivers_turnright_B2);

	sett.setValue("DRIVERS/forward_A1", m_nDrivers_forward_A1);
	sett.setValue("DRIVERS/forward_A2", m_nDrivers_forward_A2);
	sett.setValue("DRIVERS/forward_B1", m_nDrivers_forward_B1);
	sett.setValue("DRIVERS/forward_B2", m_nDrivers_forward_B2);

	sett.setValue("DRIVERS/backward_A1", m_nDrivers_backward_A1);
	sett.setValue("DRIVERS/backward_A2", m_nDrivers_backward_A2);
	sett.setValue("DRIVERS/backward_B1", m_nDrivers_backward_B1);
	sett.setValue("DRIVERS/backward_B2", m_nDrivers_backward_B2);

	return true;
}

// ---------------------------------------------------------------------

int Settings::get_port(){
	return m_nPort;
}

// ---------------------------------------------------------------------

void Settings::set_port(int v){
	m_nPort = v;
	this->save();
}

// ---------------------------------------------------------------------

QString Settings::get_secret(){
	return m_sSecret;
}

// ---------------------------------------------------------------------

void Settings::set_secret(QString s){
	m_sSecret = s;
	this->save();
}

// ---------------------------------------------------------------------

int Settings::get_servo_pin_comb(){
	return m_nServo_PinComb;
}

// ---------------------------------------------------------------------

void Settings::set_servo_pin_comb(int v) {
	m_nServo_PinComb = v;
	this->save();
}

// ---------------------------------------------------------------------

int Settings::get_servo_pin_comb_value_up(){
	return m_nServo_PinComb_value_up;
}

// ---------------------------------------------------------------------

void Settings::set_servo_pin_comb_value_up(int v){
	m_nServo_PinComb_value_up = v;
	this->save();
}

// ---------------------------------------------------------------------

int Settings::get_servo_pin_comb_value_down(){
	return m_nServo_PinComb_value_down;
}

// ---------------------------------------------------------------------

void Settings::set_servo_pin_comb_value_down(int v){
	m_nServo_PinComb_value_down = v;
	this->save();
}

// ---------------------------------------------------------------------

int Settings::get_drivers_pin_A1(){
	return m_nDrivers_PIN_A1;
}

// ---------------------------------------------------------------------

void Settings::set_drivers_pin_A1(int v){
	m_nDrivers_PIN_A1 = v;
	this->save();
}
		
// ---------------------------------------------------------------------

int Settings::get_drivers_pin_A2(){
	return m_nDrivers_PIN_A2;
}
		
// ---------------------------------------------------------------------

void Settings::set_drivers_pin_A2(int v){
	m_nDrivers_PIN_A2 = v;
	this->save();
}

// ---------------------------------------------------------------------

int Settings::get_drivers_pin_B1(){
	return m_nDrivers_PIN_B1;
}

// ---------------------------------------------------------------------

void Settings::set_drivers_pin_B1(int v){
	m_nDrivers_PIN_B1 = v;
	this->save();
}

// ---------------------------------------------------------------------

int Settings::get_drivers_pin_B2(){
	return m_nDrivers_PIN_B2;
}

// ---------------------------------------------------------------------

void Settings::set_drivers_pin_B2(int v){
	m_nDrivers_PIN_B2 = v;
	this->save();
}

// ---------------------------------------------------------------------
		
int Settings::get_drivers_turnleft_A1(){
	return m_nDrivers_turnleft_A1;
}

// ---------------------------------------------------------------------

void Settings::set_drivers_turnleft_A1(int v){
	m_nDrivers_turnleft_A1 = v;
	this->save();
}

// ---------------------------------------------------------------------

int Settings::get_drivers_turnleft_A2(){
	return m_nDrivers_turnleft_A2;
}

// ---------------------------------------------------------------------

void Settings::set_drivers_turnleft_A2(int v){
	m_nDrivers_turnleft_A2 = v;
	this->save();
}

// ---------------------------------------------------------------------

int Settings::get_drivers_turnleft_B1(){
	return m_nDrivers_turnleft_B1;
}

// ---------------------------------------------------------------------

void Settings::set_drivers_turnleft_B1(int v){
	m_nDrivers_turnleft_B1 = v;
	this->save();
}

// ---------------------------------------------------------------------

int Settings::get_drivers_turnleft_B2(){
	return m_nDrivers_turnleft_B2;
}

// ---------------------------------------------------------------------

void Settings::set_drivers_turnleft_B2(int v){
	m_nDrivers_turnleft_B2 = v;
	this->save();
}

// ---------------------------------------------------------------------

int Settings::get_drivers_turnright_A1(){
	return m_nDrivers_turnright_A1;
}

// ---------------------------------------------------------------------

void Settings::set_drivers_turnright_A1(int v){
	m_nDrivers_turnright_A1 = v;
	this->save();
}

// ---------------------------------------------------------------------

int Settings::get_drivers_turnright_A2(){
	return m_nDrivers_turnright_A2;
}

// ---------------------------------------------------------------------

void Settings::set_drivers_turnright_A2(int v){
	m_nDrivers_turnright_A2 = v;
	this->save();
}

// ---------------------------------------------------------------------

int Settings::get_drivers_turnright_B1(){
	return m_nDrivers_turnright_B1;
}

// ---------------------------------------------------------------------

void Settings::set_drivers_turnright_B1(int v){
	m_nDrivers_turnright_B1 = v;
	this->save();
}

// ---------------------------------------------------------------------

int Settings::get_drivers_turnright_B2(){
	return m_nDrivers_turnright_B2;
}

// ---------------------------------------------------------------------

void Settings::set_drivers_turnright_B2(int v){
	m_nDrivers_turnright_B2 = v;
	this->save();
}

// ---------------------------------------------------------------------

int Settings::get_drivers_forward_A1(){
	return m_nDrivers_forward_A1;
}

// ---------------------------------------------------------------------

void Settings::set_drivers_forward_A1(int v){
	m_nDrivers_forward_A1 = v;
	this->save();
}

// ---------------------------------------------------------------------

int Settings::get_drivers_forward_A2(){
	return m_nDrivers_forward_A2;
}

// ---------------------------------------------------------------------

void Settings::set_drivers_forward_A2(int v){
	m_nDrivers_forward_A2 = v;
	this->save();
}

// ---------------------------------------------------------------------

int Settings::get_drivers_forward_B1(){
	return m_nDrivers_forward_B1;
}

// ---------------------------------------------------------------------

void Settings::set_drivers_forward_B1(int v){
	m_nDrivers_forward_B1 = v;
	this->save();
}

// ---------------------------------------------------------------------

int Settings::get_drivers_forward_B2(){
	return m_nDrivers_forward_B2;
}

// ---------------------------------------------------------------------

void Settings::set_drivers_forward_B2(int v){
	m_nDrivers_forward_B2 = v;
	this->save();
}

// ---------------------------------------------------------------------

int Settings::get_drivers_backward_A1(){
	return m_nDrivers_backward_A1;
}

// ---------------------------------------------------------------------

void Settings::set_drivers_backward_A1(int v){
	m_nDrivers_backward_A1 = v;
	this->save();
}

// ---------------------------------------------------------------------

int Settings::get_drivers_backward_A2(){
	return m_nDrivers_backward_A2;
}

// ---------------------------------------------------------------------

void Settings::set_drivers_backward_A2(int v){
	m_nDrivers_backward_A2 = v;
	this->save();
}

// ---------------------------------------------------------------------

int Settings::get_drivers_backward_B1(){
	return m_nDrivers_backward_B1;
}

// ---------------------------------------------------------------------

void Settings::set_drivers_backward_B1(int v){
	m_nDrivers_backward_B1 = v;
	this->save();
}

// ---------------------------------------------------------------------

int Settings::get_drivers_backward_B2(){
	return m_nDrivers_backward_B2;
}

// ---------------------------------------------------------------------

void Settings::set_drivers_backward_B2(int v){
	m_nDrivers_backward_B2 = v;
	this->save();
}

// ---------------------------------------------------------------------
