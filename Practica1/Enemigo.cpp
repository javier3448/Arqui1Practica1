// 
// 
// 

#include "Enemigo.h"
#include "PlayableArea.h"

unsigned int EnemigoClass::tickCount = 0;
unsigned int EnemigoClass::tickFrequency = 100;

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
	if (tickCount >= tickFrequency) {
		clearPart();
		char yVirtual = yPos + 1;
		if (yVirtual >= GAME_ARRAY_SIZE - 1)
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
	if (tickCount >= tickFrequency) 
	{
		tickCount = 0;
	}
}

void EnemigoClass::redraw()
{
	Serial.print("posy: ");
	Serial.println((int)yPos);
	playableArea.drawOnes(xPos, yPos, sprite, SIZEOF_ENEMY_SPRITE);
}

void EnemigoClass::clearPart()
{
	playableArea.clearOnes(xPos, yPos, sprite, SIZEOF_ENEMY_SPRITE);
}

void EnemigoClass::destroy()
{
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
