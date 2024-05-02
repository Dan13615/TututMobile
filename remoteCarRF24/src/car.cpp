/**********************************************************************
  Project     : TututMobile
  Description : A RF24 Remote Car.
  Author      : Daniil Stepanov
**********************************************************************/

#include "../include/tututMobile.h"

float batteryVoltage = 0;
bool isBuzzered = false;

void motorRun(int speedl, int speedr)
{
	int dirL = 0;
	int dirR = 0;

	if (speedl > 0)
		dirL = 0 ^ MOTOR_DIRECTION;
	else {
		dirL = 1 ^ MOTOR_DIRECTION;
		speedl = -speedl;
	}
	if (speedr > 0)
		dirR = 1 ^ MOTOR_DIRECTION;
	else {
		dirR = 0 ^ MOTOR_DIRECTION;
		speedr = -speedr;
	}
	speedl = constrain(speedl, 0, 255);
	speedr = constrain(speedr, 0, 255);
	if (abs(speedl) < MOTOR_PWM_DEAD && abs(speedr) < MOTOR_PWM_DEAD) {
		speedl = 0;
		speedr = 0;
	}
	digitalWrite(PIN_DIRECTION_LEFT, dirL);
	digitalWrite(PIN_DIRECTION_RIGHT, dirR);
	analogWrite(PIN_MOTOR_PWM_LEFT, speedl);
	analogWrite(PIN_MOTOR_PWM_RIGHT, speedr);
}

bool getBatteryVoltage()
{
	int batteryADC = 0;

	if (!isBuzzered) {
		pinMode(PIN_BATTERY, INPUT);
		batteryADC = analogRead(PIN_BATTERY);
		if (batteryADC < 614) {
			batteryVoltage = batteryADC / 1023.0 * 5.0 * 4;
			return true;
		}
	}
	return false;
}

void setBuzzer(bool flag)
{
	isBuzzered = flag;
	pinMode(PIN_BUZZER, flag);
	digitalWrite(PIN_BUZZER, flag);
}

void alarm(u8 beat, u8 repeat)
{
	beat = constrain(beat, 1, 9);
	repeat = constrain(repeat, 1, 255);
	for (int j = 0; j < repeat; j++) {
		for (int i = 0; i < beat; i++) {
			setBuzzer(true);
			delay(100);
			setBuzzer(false);
			delay(100);
		}
		delay(500);
	}
}

void resetCarAction()
{
	motorRun(0, 0);
	setBuzzer(false);
}

void detectWall()
{
	long duration = 0;
	float distance_cm = 0;

	digitalWrite(PIN_SONIC_TRIG, LOW);
	delayMicroseconds(2);
	digitalWrite(PIN_SONIC_TRIG, HIGH);
	delayMicroseconds(10);
	digitalWrite(PIN_SONIC_TRIG, LOW);
	duration = pulseIn(PIN_SONIC_ECHO, HIGH);
	distance_cm = duration * 0.034 / 2;
	if (distance_cm < 20)
		stopCar();
	else
		setBuzzer(false);
	delay(15);
}

void stopCar()
{
	resetCarAction();
	setBuzzer(true);
	digitalWrite(PIN_DIRECTION_LEFT, LOW);
	digitalWrite(PIN_DIRECTION_RIGHT, HIGH);
	analogWrite(PIN_MOTOR_PWM_LEFT, 100);
	analogWrite(PIN_MOTOR_PWM_RIGHT, 100);
	delay(1000);
	digitalWrite(PIN_DIRECTION_LEFT, HIGH);
	digitalWrite(PIN_DIRECTION_RIGHT, LOW);
	analogWrite(PIN_MOTOR_PWM_LEFT, 0);
	analogWrite(PIN_MOTOR_PWM_RIGHT, 0);
	setBuzzer(false);
}