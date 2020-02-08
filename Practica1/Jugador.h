// Jugador.h

#ifndef _JUGADOR_h
#define _JUGADOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define SIZEOF_PLAYER_SPRITE 2

class JugadorClass
{ 
 private:
	 static byte sprite[SIZEOF_PLAYER_SPRITE] ;
	 char xPos;
	 const char yPos = 14;
	 void clearPart();

 public:
	 JugadorClass(char xPos);
	 //false si murio
	 bool tryUpdate(char dir);
	 bool tryMove(char dir);
	 void redraw();
};


#endif

