// PlayableArea.h

#ifndef _PLAYABLEAREA_h
#define _PLAYABLEAREA_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define GAME_ARRAY_SIZE 16

class PlayableAreaClass
{
public:
	//gameArray podria ser private o protected pero que hueva
	//Si quisieramos incrementar el tamanno de la pantalla a la derecha tenenmos que cambiar byte por short, int o cualquier otro numero con mas capacidad
	byte gameArray[GAME_ARRAY_SIZE] = {//MATRIX 1
		0x01,
		0x02,
		0x03,
		0x04,
		0x05,
		0x06,
		0x07,
		0x08,
		//MATRIX 2
		0x09,
		0x0a,
		0x0b,
		0x0c,
		0x0d,
		0x0e,
		0x0f,
		0x10 };

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
