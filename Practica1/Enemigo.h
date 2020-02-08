// Enemigo.h

#ifndef _ENEMIGO_h
#define _ENEMIGO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define SIZEOF_ENEMY_SPRITE 2

class EnemigoClass
{
private:
	static byte sprite[SIZEOF_ENEMY_SPRITE];
	static unsigned int tickCount;
	static unsigned int tickFrequency;
	char xPos;
	char yPos;
	void clearPart();


public:
	static const char NOTHING = 0;
	static const char DIES = 1;
	static const char KILLS = 2;

	bool isNull =true;

	EnemigoClass(char xPos, char yPos);
	EnemigoClass();
	//KILLS: si mato al jugador, DIES: si salio de la pantalla, NOTHING: si no pasa nada
	char update();
	void redraw();
	void destroy();
};


#endif

