// Jugador.h

#ifndef _JUGADOR_h
#define _JUGADOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define SIZEOF_PLAYER_SPRITE

class JugadorClass
{
 private:
	 byte sprite[SIZEOF_PLAYER_SPRITE];
	 char xPos;
	 char yPos;

 public:
	 //false si murio
	 bool tryUpdate(char dir);

};


#endif

