/**********************************************************************
  Project     : TututMobile
  Description : A RF24 Remote Car.
  Author      : Daniil Stepanov
**********************************************************************/

#ifndef _NRF_REMOTE_h
	#define _NRF_REMOTE_h

	#if defined(ARDUINO) && ARDUINO >= 100
		#include "Arduino.h"
	#else
		#include "WProgram.h"
	#endif

	#include "tututMobile.h"

extern RF24 radio;
extern int nrfDataRead[8];

bool nrf24L01Setup();
void checkNrfReceived();
bool getNrf24L01Data();
void clearNrfFlag();
void updateCarActionByNrfRemote();
void resetNrfDataBuf();
u8 updateNrfCarMode();

#endif
