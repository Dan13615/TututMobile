/**********************************************************************
* Filename    : remoteControllerRF24.ino
* Product     : 4WD Car for ArduinoUNO
* Description : Code for RF24 Remote Controller.
* Author      : Dan13615
**********************************************************************/
// NRF24L01

#include <SPI.h>
#include "RF24.h"

RF24 radio(9, 10);
const byte addresses[6] = "Free1";
int dataWrite[8];

#define potentiometer1Pin   = A0;
#define potentiometer2Pin   = A1;
#define joystickXPin        = A2;
#define joystickYPin        = A3;
#define joystickZPin        = 7;
#define s1Pin               = 4;
#define s2Pin               = 3;
#define s3Pin               = 2;
#define led1Pin             = 6;
#define led2Pin             = 5;
#define led3Pin             = 8;

void setup()
{
    radio.begin();
    radio.setPALevel(RF24_PA_MAX);
    radio.setDataRate(RF24_1MBPS);
    radio.setRetries(0, 15);
    radio.openWritingPipe(addresses);
    radio.openReadingPipe(1, addresses);
    radio.stopListening();
    pinMode(joystickZPin, INPUT);
    pinMode(s1Pin, INPUT);
    pinMode(s2Pin, INPUT);
    pinMode(s3Pin, INPUT);
    pinMode(led1Pin, OUTPUT);
    pinMode(led2Pin, OUTPUT);
    pinMode(led3Pin, OUTPUT);
}

void loop()
{
    dataWrite[0] = analogRead(potentiometer1Pin);
    dataWrite[1] = analogRead(potentiometer2Pin);
    dataWrite[2] = analogRead(joystickXPin);
    dataWrite[3] = analogRead(joystickYPin);
    dataWrite[4] = digitalRead(joystickZPin);
    dataWrite[5] = digitalRead(s1Pin);
    dataWrite[6] = digitalRead(s2Pin);
    dataWrite[7] = digitalRead(s3Pin);
    if (radio.writeFast(&dataWrite, sizeof(dataWrite)))
        digitalWrite(led3Pin, HIGH);
    else
        digitalWrite(led3Pin, LOW);
    delay(20);
    analogWrite(led1Pin, map(dataWrite[0], 0, 1023, 0, 255));
    analogWrite(led2Pin, map(dataWrite[1], 0, 1023, 0, 255));
}
