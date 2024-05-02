/**********************************************************************
  Project     : TututMobile
  Description : A RF24 Remote Car.
  Author      : Daniil Stepanov
**********************************************************************/

#include "../include/tututMobile.h"

RF24 radio(PIN_SPI_CE, PIN_SPI_CSN);
const byte addresses[6] = "Free1";
int nrfDataRead[8];
bool nrfComplete = false;

bool nrf24L01Setup()
{
    if (radio.begin()) {
        radio.setPALevel(RF24_PA_MAX);
        radio.setDataRate(RF24_1MBPS);
        radio.setRetries(0, 15);
        radio.openWritingPipe(addresses);
        radio.openReadingPipe(1, addresses);
        radio.startListening();
        FlexiTimer2::set(20, 1.0 / 1000, checkNrfReceived);
        FlexiTimer2::start();
        return true;
    }
    return false;
}

void checkNrfReceived()
{
    delayMicroseconds(1000);
    if (radio.available()) {
        while (radio.available())
            radio.read(nrfDataRead, sizeof(nrfDataRead));
    nrfComplete = true;
    return;
    }
    nrfComplete = false;
}

bool getNrf24L01Data()
{
    return nrfComplete;
}

void clearNrfFlag()
{
    nrfComplete = 0;
}

void updateCarActionByNrfRemote()
{
    int x = nrfDataRead[2] - 512;
    int y = nrfDataRead[3] - 512;
    int pwmL = 0;
    int pwmR = 0;

    if (y < 0) {
        pwmL = (-y + x) / 2;
        pwmR = (-y - x) / 2;
    }
    else {
        pwmL = (-y - x) / 2;
        pwmR = (-y + x) / 2;
    }
    motorRun(pwmL, pwmR);
    if (nrfDataRead[4] == 0)
        setBuzzer(true);
    else
        setBuzzer(false);
}

void resetNrfDataBuf()
{
    nrfDataRead[0] = 0;
    nrfDataRead[1] = 0;
    nrfDataRead[2] = 512;
    nrfDataRead[3] = 512;
    nrfDataRead[4] = 1;
    nrfDataRead[5] = 1;
    nrfDataRead[6] = 1;
    nrfDataRead[7] = 1;
}

u8 updateNrfCarMode()
{
    return ((nrfDataRead[5] == 1 ? 1 : 0) << 2) |
    ((nrfDataRead[6] == 1 ? 1 : 0) << 1) |
    ((nrfDataRead[7] == 1 ? 1 : 0) << 0);
}
