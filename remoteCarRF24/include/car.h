/**********************************************************************
  Project     : TututMobile
  Description : A RF24 Remote Car.
  Author      : Daniil Stepanov
**********************************************************************/

#ifndef _CAR_H
    #define _CAR_H

    #if defined(ARDUINO) && ARDUINO >= 100
        #include "Arduino.h"
    #else
        #include "WProgram.h"
    #endif

    #include "tututMobile.h"

extern float batteryVoltage;

void motorRun(int speedl, int speedr);
bool getBatteryVoltage();
void setBuzzer(bool flag);
void alarm(u8 beat, u8 repeat);
void resetCarAction();
void detectWall();
void stopCar();

#endif
