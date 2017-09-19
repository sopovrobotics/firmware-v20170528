#ifndef SETTINIGS_H
#define SETTINIGS_H

#include <QObject>
#include <QString>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QMap>
#include <QElapsedTimer>
#include <QThread>
#include <QSettings>
#include "interfaces/icmdhandler.h"
#include "interfaces/icontrolserver.h"

// QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
// QT_FORWARD_DECLARE_CLASS(QWebSocket)

class Settings : public ISettings {

	public:
		Settings();
		virtual int get_port();
		virtual void set_port(int);
		virtual QString get_secret();
		virtual void set_secret(QString s);
		
		virtual int get_servo_pin_comb();
		virtual void set_servo_pin_comb(int v);
		virtual int get_servo_pin_comb_value_up();
		virtual void set_servo_pin_comb_value_up(int v);
		virtual int get_servo_pin_comb_value_down();
		virtual void set_servo_pin_comb_value_down(int v);

		virtual int get_drivers_pin_A1();
		virtual void set_drivers_pin_A1(int);
		virtual int get_drivers_pin_A2();
		virtual void set_drivers_pin_A2(int);
		virtual int get_drivers_pin_B1();
		virtual void set_drivers_pin_B1(int);
		virtual int get_drivers_pin_B2();
		virtual void set_drivers_pin_B2(int);
	
		virtual int get_drivers_turnleft_A1();
		virtual void set_drivers_turnleft_A1(int);
		virtual int get_drivers_turnleft_A2();
		virtual void set_drivers_turnleft_A2(int);
		virtual int get_drivers_turnleft_B1();
		virtual void set_drivers_turnleft_B1(int);
		virtual int get_drivers_turnleft_B2();
		virtual void set_drivers_turnleft_B2(int);

		virtual int get_drivers_turnright_A1();
		virtual void set_drivers_turnright_A1(int);
		virtual int get_drivers_turnright_A2();
		virtual void set_drivers_turnright_A2(int);
		virtual int get_drivers_turnright_B1();
		virtual void set_drivers_turnright_B1(int);
		virtual int get_drivers_turnright_B2();
		virtual void set_drivers_turnright_B2(int);
	
		virtual int get_drivers_forward_A1();
		virtual void set_drivers_forward_A1(int);
		virtual int get_drivers_forward_A2();
		virtual void set_drivers_forward_A2(int);
		virtual int get_drivers_forward_B1();
		virtual void set_drivers_forward_B1(int);
		virtual int get_drivers_forward_B2();
		virtual void set_drivers_forward_B2(int);

		virtual int get_drivers_backward_A1();
		virtual void set_drivers_backward_A1(int);
		virtual int get_drivers_backward_A2();
		virtual void set_drivers_backward_A2(int);
		virtual int get_drivers_backward_B1();
		virtual void set_drivers_backward_B1(int);
		virtual int get_drivers_backward_B2();
		virtual void set_drivers_backward_B2(int);
		
	private:

		int readIntFromSettings(QSettings &sett, QString settName, int defaultValue);
		QString readStringFromSettings(QSettings &sett, QString settName, QString defaultValue);
		QStringList readStringListFromSettings(QSettings &sett, QString settName, QStringList defaultValue);
		bool readBooleanFromSettings(QSettings &sett, QString settName, bool defaultValue);
	
		bool load();
		bool save();
	
		QString m_sFilename;
		
		int m_nPort;
		QString m_sSecret;
		
		int m_nServo_PinComb;
		int m_nServo_PinComb_value_up;
		int m_nServo_PinComb_value_down;
		
		
		int m_nDrivers_PIN_A1;
		int m_nDrivers_PIN_A2;
		int m_nDrivers_PIN_B1;
		int m_nDrivers_PIN_B2;
	
		int m_nDrivers_turnleft_A1;
		int m_nDrivers_turnleft_A2;
		int m_nDrivers_turnleft_B1;
		int m_nDrivers_turnleft_B2;

		int m_nDrivers_turnright_A1;
		int m_nDrivers_turnright_A2;
		int m_nDrivers_turnright_B1;
		int m_nDrivers_turnright_B2;
	
		int m_nDrivers_forward_A1;
		int m_nDrivers_forward_A2;
		int m_nDrivers_forward_B1;
		int m_nDrivers_forward_B2;

		int m_nDrivers_backward_A1;
		int m_nDrivers_backward_A2;
		int m_nDrivers_backward_B1;
		int m_nDrivers_backward_B2;
		
		
};

#endif // SETTINIGS_H
