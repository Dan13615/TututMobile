/**********************************************************************
  Project     : TututMobile
  Description : A RF24 Remote Car.
  Author      : Daniil Stepanov
**********************************************************************/

#include "include/tututMobile.h"

float lastNrfUpdateTime = 0;

void setup()
{
    pinMode(PIN_DIRECTION_LEFT, OUTPUT);
    pinMode(PIN_MOTOR_PWM_LEFT, OUTPUT);
    pinMode(PIN_DIRECTION_RIGHT, OUTPUT);
    pinMode(PIN_MOTOR_PWM_RIGHT, OUTPUT);
    pinMode(PIN_SONIC_TRIG, OUTPUT);
    pinMode(PIN_SONIC_ECHO, INPUT);
    setBuzzer(false);
    if (!nrf24L01Setup())
        alarm(4, 2);
}

void loop()
{
    detectWall();
    if (getNrf24L01Data()) {
        clearNrfFlag();
        updateCarActionByNrfRemote();
        lastNrfUpdateTime = millis();
    }
    if (millis() - lastNrfUpdateTime > NRF_UPDATE_TIMEOUT) {
        lastNrfUpdateTime = millis();
        resetNrfDataBuf();
        updateCarActionByNrfRemote();
    }
}
