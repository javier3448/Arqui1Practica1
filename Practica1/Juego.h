// Juego.h

#ifndef _JUEGO_h
#define _JUEGO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Jugador.h"
#include "Enemigo.h"

#define SIZEOF_ENEMIGOS 4

class JuegoClass
{
 private:
	 byte conteoSeg = 0;
	 void paintByte(byte num);
	 unsigned long inicioTiempo = 0;
	 JugadorClass jugador = JugadorClass(3);

	 EnemigoClass enemigos[SIZEOF_ENEMIGOS];
 public:
	 bool paintSegs = true;
	 JuegoClass();
	 //retorna falso si murio
	 bool tryUpdate(bool isLeftPressed, bool wasLeftPressed, bool isRightPressed, bool wasRightPressed);
	 void spawnEnemigos();
	 //Lleva conteo de segundos y maneja los incrementos de velocidad
	 void cronometro();
	 void pauseAndPrintScore();
	 void reset();
	 void draw();

};

#endif

