// 
// 
// 

#include "Enemigo.h"
#include "PlayableArea.h"

int EnemigoClass::tickCount = 0;
int EnemigoClass::tickPeriod = 200;

byte EnemigoClass::sprite[SIZEOF_ENEMY_SPRITE] = {
												     0b11100000,
													 0b01000000
												 };


EnemigoClass::operator bool() const
{
	return !isNull;
}

EnemigoClass::EnemigoClass(char xPos, char yPos)
{
	isNull = false;
	this->xPos = xPos;
	this->yPos = yPos;
}

EnemigoClass::EnemigoClass()
{
	isNull = true;
}

//startUpdate y endUpdate son un chapuz para que todos los carros tengan el mismo conteo y todos se muevan al mismo tiempo

void EnemigoClass::startUpdate()
{
	tickCount++;
}

char EnemigoClass::update()
{
	if (tickCount >= tickPeriod) {
		clearPart();
		char yVirtual = yPos + 1;
		if (yVirtual >= (GAME_ARRAY_SIZE - 1))
		{
			return DIES;
		}
		if (yVirtual > 12 && playableArea.collides(xPos, yVirtual, sprite, SIZEOF_ENEMY_SPRITE))
		{
			return KILLS;
		}
		yPos = yVirtual;
		redraw();
	}
	return NOTHING;
}

void EnemigoClass::endUpdate()
{
	if (tickCount >= tickPeriod) 
	{
		tickCount = 0;
	}
}

void EnemigoClass::reset()
{
	tickCount = 0;
	tickPeriod = 200;
}

void EnemigoClass::increaseTickFrequency()
{
	if (tickPeriod - 25 > 0) //Chequea que no pase overflow. Talvez sea mejor usar una variable con signo en vez de chequear overflow
	{
		tickPeriod -= 25;
	}
}

void EnemigoClass::redraw()
{
	playableArea.drawOnes(xPos, yPos, sprite, SIZEOF_ENEMY_SPRITE);
}

void EnemigoClass::clearPart()
{
	playableArea.clearOnes(xPos, yPos, sprite, SIZEOF_ENEMY_SPRITE);
}

void EnemigoClass::destroy()
{
	clearPart();
	isNull = true;
}

char EnemigoClass::getXPos()
{
	return xPos;
}

char EnemigoClass::getYPos()
{
	return yPos;
}
