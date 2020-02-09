// 
// 
// 

#include "Jugador.h"
#include "PlayableArea.h"

byte JugadorClass::sprite[SIZEOF_PLAYER_SPRITE] = {
													  0b01000000,
													  0b11100000
												  };

void JugadorClass::redraw()
{
	playableArea.drawOnes(xPos, yPos, sprite, SIZEOF_PLAYER_SPRITE);
}

void JugadorClass::clearPart()
{
	playableArea.clearOnes(xPos, yPos, sprite, SIZEOF_PLAYER_SPRITE);
}

JugadorClass::JugadorClass(char xPos)
{
	this->xPos = xPos;
}

bool JugadorClass::tryUpdate(char dir)
{
	if (dir) {
		tryMove(dir);
	}
	return true;
}

//false si murio
bool JugadorClass::tryMove(char dir)
{
	clearPart();
	char xVirtual = xPos + dir;
	if (xVirtual < 0 || xVirtual > (sizeof(playableArea.gameArray[0]) * 8) - 3) {
		redraw();
		return true;
	}
	if (playableArea.collides(xVirtual, yPos, sprite, SIZEOF_PLAYER_SPRITE))
	{
		//murio
		return false;
	}
	xPos = xVirtual;
	redraw();
	return true;
}

void JugadorClass::setXPos(char xPos)
{
	this->xPos = xPos;
}




