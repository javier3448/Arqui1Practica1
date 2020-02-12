// Mensaje.h

#ifndef _MENSAJE_h
#define _MENSAJE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MensajeClass
{
 protected:


 public:
	 int secuencia[25] = { 1,15,14,2,3,4,5,5,6,7,8,13,9,2,10,11,9,5,12,6,5,9,15};
	 MensajeClass();
	 void setUp(long v, char sense);
	 void prueba();
	 void bajar();
	 void subir();
	 void mover(int sn);
};

extern MensajeClass Mensaje;

#endif

