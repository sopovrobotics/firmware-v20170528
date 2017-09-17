#ifndef INTERFACES_ISETTINGS_H
#define INTERFACES_ISETTINGS_H

#include <QJsonObject>

class ISettings {
	public:
		virtual int get_port() = 0;

		virtual int get_servo_pin_comb() = 0;
		virtual void set_servo_pin_comb(int v) = 0;
		virtual int get_servo_pin_comb_value_up() = 0;
		virtual void set_servo_pin_comb_value_up(int v) = 0;
		virtual int get_servo_pin_comb_value_down() = 0;
		virtual void set_servo_pin_comb_value_down(int v) = 0;

		virtual int get_drivers_pin_A1() = 0;
		virtual void set_drivers_pin_A1(int v) = 0;
		virtual int get_drivers_pin_A2() = 0;
		virtual void set_drivers_pin_A2(int) = 0;
		virtual int get_drivers_pin_B1() = 0;
		virtual void set_drivers_pin_B1(int) = 0;
		virtual int get_drivers_pin_B2() = 0;
		virtual void set_drivers_pin_B2(int) = 0;
		
		virtual int get_drivers_turnleft_A1() = 0;
		virtual void set_drivers_turnleft_A1(int) = 0;
		virtual int get_drivers_turnleft_A2() = 0;
		virtual void set_drivers_turnleft_A2(int) = 0;
		virtual int get_drivers_turnleft_B1() = 0;
		virtual void set_drivers_turnleft_B1(int) = 0;
		virtual int get_drivers_turnleft_B2() = 0;
		virtual void set_drivers_turnleft_B2(int v) = 0;

		virtual int get_drivers_turnright_A1() = 0;
		virtual void set_drivers_turnright_A1(int) = 0;
		virtual int get_drivers_turnright_A2() = 0;
		virtual void set_drivers_turnright_A2(int) = 0;
		virtual int get_drivers_turnright_B1() = 0;
		virtual void set_drivers_turnright_B1(int) = 0;
		virtual int get_drivers_turnright_B2() = 0;
		virtual void set_drivers_turnright_B2(int) = 0;
	
		virtual int get_drivers_forward_A1() = 0;
		virtual void set_drivers_forward_A1(int) = 0;
		virtual int get_drivers_forward_A2() = 0;
		virtual void set_drivers_forward_A2(int) = 0;
		virtual int get_drivers_forward_B1() = 0;
		virtual void set_drivers_forward_B1(int) = 0;
		virtual int get_drivers_forward_B2() = 0;
		virtual void set_drivers_forward_B2(int) = 0;

		virtual int get_drivers_backward_A1() = 0;
		virtual void set_drivers_backward_A1(int) = 0;
		virtual int get_drivers_backward_A2() = 0;
		virtual void set_drivers_backward_A2(int) = 0;
		virtual int get_drivers_backward_B1() = 0;
		virtual void set_drivers_backward_B1(int) = 0;
		virtual int get_drivers_backward_B2() = 0;
		virtual void set_drivers_backward_B2(int) = 0;
};

#endif // INTERFACES_ISETTINGS_H
