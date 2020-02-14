// 
// 
// 

#include "PlayableArea.h"

extern PlayableAreaClass playableArea = PlayableAreaClass();//chapuz maximo para hacer un como singleton chafa

void PlayableAreaClass::clear()
{
	memset(gameArray, 0, GAME_ARRAY_SIZE);
}

void PlayableAreaClass::fill()//clear y fill podrian ser es mismo metodo solo parasar el valor de memset como parametro
{
	memset(gameArray, 0xff, GAME_ARRAY_SIZE);
}

void PlayableAreaClass::drawGameOver(char gameOverScene)//TODO: mejor nombre para type
{
	switch (gameOverScene)
	{
	default:
		clear();
		byte start = 6;
		gameArray[start] = 0b00100100;
		//gameArray[start + 1] = 0b00000000;
		gameArray[start + 2] = 0b00111100;
		gameArray[start + 3] = 0b01000010;
		break;
	}
}

//Funcionan todas las bitwise tan bien porque el numero de pixeles horizontales del gameArray es exactamente 8 bits (1byte). Si quisieramos una pantalla con un numero no multiplo de 8 se aruina todo
void PlayableAreaClass::drawOnes(char x, char y, byte data[], byte sizeOfData)
{
	if (x >= (char)sizeof(gameArray[0]) * 8 || y >= GAME_ARRAY_SIZE)//|| y >= GAME_ARRAY_SIZE no es necesario
		return;

	for (byte i = 0; i < sizeOfData && i + y < GAME_ARRAY_SIZE; i++)
	{
		char currY = i + y;
		if (currY < 0)
			continue;
		byte currData = data[i];
		if (x < 0)
			currData = currData << -x;//Quita el negativo
		else
			currData = currData >> x;
		gameArray[currY] |= currData;
	}
}

void PlayableAreaClass::clearOnes(char x, char y, byte data[], byte sizeOfData)
{
	if (x >= (char)sizeof(gameArray[0]) * 8 || y >= GAME_ARRAY_SIZE)
		return;

	for (byte i = 0; i < sizeOfData && i + y < GAME_ARRAY_SIZE; i++)
	{
		char currY = i + y;
		if (currY < 0)
			continue;
		byte currData = data[i];
		if (x < 0) 
			currData = currData << -x;//Quita el negativo
		else
			currData = currData >> x;
		currData = ~currData;
		gameArray[currY] &= currData;
	}
}

void PlayableAreaClass::drawOnesInRow(char x, char y, byte data)
{
	if (x >= (char)sizeof(gameArray[0]) * 8 || y >= GAME_ARRAY_SIZE)
		return;

	byte currData = data;
	if (x < 0)
		currData = currData << -x;
	else
		currData = currData >> x;
	gameArray[y] |= currData;
}

void PlayableAreaClass::draw(char x, char y, byte data[], byte sizeOfData)
{
	if (x >= (char)sizeof(gameArray[0]) * 8 || y >= GAME_ARRAY_SIZE)
		return;

	for (byte i = 0; i < sizeOfData && i + y < GAME_ARRAY_SIZE; i++)
	{
		char currY = i + y;
		if (currY < 0)
			continue;
		//El ~ es un Chapuz para que shiftee 1s y no 0s
		byte currData = data[i];
		if (x < 0)
			currData = currData << -x;//Quita el negativo
		else
			currData = currData >> x;
		byte auxData = 0xff;
		auxData = auxData >> x;
		auxData = ~auxData;

		gameArray[currY] &= auxData;
		gameArray[currY] |= currData;
	}
}

void PlayableAreaClass::drawRow(char x, char y, byte data)
{
	if (x >= (char)sizeof(gameArray[0]) * 8 || y >= GAME_ARRAY_SIZE || y < 0)
		return;

	//El ~ es un Chapuz para que shiftee 1s y no 0s. tiene que existir una mejor manaera de hacer estas operaciones bitwise
	byte currData = data;
	if (x < 0)
		currData = currData << -x;//Quita el negativo
	else
		currData = currData >> x;
	byte auxData = 0xff;
	auxData = auxData >> x;
	auxData = ~auxData;

	gameArray[y] &= auxData;
	gameArray[y] |= currData;
}

bool PlayableAreaClass::collides(char x, char y, byte buffer[], byte sizeOfData)//x<0 y<0  va a dar true algunos casos. Siempre y cuando las piezas empizas tenga llena la pos 0,0 no hay problema
{
	//Talvez sea mejor hacer los 3 ciclos en 1 solo for de 0 a sizeOfData con 3 if adentro, cada if lidea con un caso (gameArrayRow a revisar: negativo, adentro de la pantalla y igual o mayor a GAME_ARRAY_SIZE)
	//No se que hice aqui, talvez sea mejor usar el drawOnes como base
	byte i = 0;
	for (; i + y < 0 && i < sizeOfData; i++)
	{
		unsigned long gameArrayRow = 0xffffffff;
		unsigned long currData = ((unsigned long)buffer[i]) << (16 - x);

		if (gameArrayRow & currData)
			return true;
	}

	for (; i + y < GAME_ARRAY_SIZE && i < sizeOfData; i++)
	{
		unsigned long gameArrayRow = ((unsigned long)gameArray[i + y]) << 16;
		gameArrayRow |= 0xff00ffff;

		unsigned long currData = ((unsigned long)buffer[i]) << (16 - x);

		if (gameArrayRow & currData)
			return true;
	}

	for (; i < sizeOfData; i++)
	{
		unsigned long gameArrayRow = 0xffffffff;
		unsigned long currData = ((unsigned long)buffer[i]) << (16 - x);

		if (gameArrayRow & currData)
			return true;
	}

	return false;
}
