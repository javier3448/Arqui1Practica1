// Juego.h

#ifndef _JUEGO_h
#define _JUEGO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class JuegoClass
{
 private:
	 byte conteoSeg = 0;
	 void paintByte(byte num);
	 unsigned long inicioTiempo = 0;

 public:
	 JuegoClass();
	 void update(bool isLeftPressed, bool wasLeftPressed, bool isRightPressed, bool wasRightPressed);
	 void pause();
	 void reset();
	
};

#endif

