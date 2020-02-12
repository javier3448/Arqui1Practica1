// Definiciones.h

#ifndef _DEFINICIONES_h
#define _DEFINICIONES_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define SIZEOF_ALF 24
#define SIZEOF_MYCHAR 8
#define SIZE_OF_MESSAGE 23

extern byte alfabeto[SIZEOF_ALF][SIZEOF_MYCHAR];
extern byte ALF_CERO;
extern char auxMensaje;
extern int POSICIONES[SIZE_OF_MESSAGE];

#endif

