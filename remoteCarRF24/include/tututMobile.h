/**********************************************************************
  Project     : TututMobile
  Description : A RF24 Remote Car.
  Author      : Daniil Stepanov
**********************************************************************/

#include "car.h"
#include "RF24Protocol.h"
#include "RF24.h"
#include <Servo.h>
#include <FlexiTimer2.h>

#define NRF_UPDATE_TIMEOUT              1000

#define MOTOR_DIRECTION     0
#define PIN_DIRECTION_LEFT	4
#define PIN_DIRECTION_RIGHT	3
#define PIN_MOTOR_PWM_LEFT	6
#define PIN_MOTOR_PWM_RIGHT	5

#define PIN_SONIC_TRIG		7
#define	PIN_SONIC_ECHO		8

#define PIN_SPI_CE			9
#define PIN_SPI_CSN			10

#define PIN_BATTERY			A0
#define PIN_BUZZER			A0

#define MOTOR_PWM_DEAD	    5