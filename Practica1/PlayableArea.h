// PlayableArea.h

#ifndef _PLAYABLEAREA_h
#define _PLAYABLEAREA_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define GAME_ARRAY_SIZE 17

class PlayableAreaClass
{
public:
	//gameArray podria ser private o protected pero que hueva
	//Si quisieramos incrementar el tamanno de la pantalla a la derecha tenenmos que cambiar byte por short, int o cualquier otro numero con mas capacidad
	byte gameArray[GAME_ARRAY_SIZE] = {//MATRIX 1
		0xff,
		0xfe,
		0xfd,
		0xfc,
		0xfb,
		0xfa,
		0xf9,
		0xf8,
		//MATRIX 2
		0xf7,
		0xf6,
		0xf5,
		0xf4,
		0xf3,
		0xf2,
		0xf1,
		0xf0,
		0xef
	};

	void clear();
	void fill();
	void drawGameOver(char gameOverScene);
	//Ignora los zeros que contienen los bytes, solo dibuja los unos sobre el array
	void drawOnes(char x, char y, byte buffer[], byte sizeOfData);
	void drawOnesInRow(char x, char y, byte data);
	//todos los 1s en data los pone en 0 en el gameArray/ Buscarle un mejor nombre a esta funcion
	void clearOnes(char x, char y, byte buffer[], byte sizeOfData);
	void draw(char x, char y, byte buffer[], byte sizeOfData);
	void drawRow(char x, char y, byte data);
	bool collides(char x, char y, byte buffer[], byte sizeOfData);
};

extern PlayableAreaClass playableArea;
#endif
