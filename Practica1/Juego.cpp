// 
// 
// 

#include "Juego.h"
#include "PlayableArea.h"
#include "Definiciones.h"


void JuegoClass::paintByte(byte num)
{
	String s = String(num);
	if (num < 9) 
	{
		s = String("0") + s;
	}
	byte firstDigit = s[s.length() - 2] - 48 + ALF_CERO;//msd
	byte secondDigit = s[s.length() - 1] - 48 + ALF_CERO;//lsd
	playableArea.draw(0, 0, alfabeto[firstDigit], SIZEOF_MYCHAR);
	playableArea.draw(0, 8, alfabeto[secondDigit], SIZEOF_MYCHAR);
}


JuegoClass::JuegoClass()
{
	
}

bool JuegoClass::tryUpdate(bool isLeftPressed, bool wasLeftPressed, bool isRightPressed, bool wasRightPressed)
{
	cronometro();

	if (isLeftPressed && !wasLeftPressed && !jugador.tryMove(-1)) {
		return false;
	}

	if (isRightPressed && !wasRightPressed && !jugador.tryMove(1)) {
		return false;
	}

	spawnEnemigos();

	EnemigoClass::startUpdate();
	for (byte i = 0; i < SIZEOF_ENEMIGOS; i++)
	{
		auto& enemy = enemigos[i];
		if (!enemy)
		{
			continue;
		}

		char enemyResult = enemy.update();
		if (enemyResult == EnemigoClass::KILLS)
		{
			return false;
		}

		if (enemyResult == EnemigoClass::DIES)
		{
			enemy.destroy();
		}//Quitar todo lo de enemy
	}
	EnemigoClass::endUpdate();

	return true;
}

void JuegoClass::spawnEnemigos()
{
	char availableIndex = -1;
	char yDistance = random(4, 7);
	for (byte i = 0; i < SIZEOF_ENEMIGOS; i++) 
	{
		if (enemigos[i]) 
		{
			if (enemigos[i].getYPos() < yDistance)
			{
				return;
			}
		}
		else
		{
			availableIndex = i;
		}
	}

	if (availableIndex >= 0) 
	{
		enemigos[availableIndex] = EnemigoClass(random(0, sizeof(playableArea.gameArray[0]) * 8 - 3), -1);
	}
}

void JuegoClass::cronometro()
{
	if (millis() - inicioTiempo >= 1000) {
		inicioTiempo = millis();
		conteoSeg++;
		if ((conteoSeg % 10) == 10)
		{
			//subir velocidad
		}
	}
}

void JuegoClass::pauseAndPrintScore()
{
	if (paintSegs) {//Variable booleana para que dibuje 1 solavez el conteno de segundos
		paintByte(conteoSeg);
		paintSegs = false;
	}
	//hacer nada
}

void JuegoClass::reset()
{
	inicioTiempo = millis();
	for (byte i = 0; i < SIZEOF_ENEMIGOS; i++)
	{
		enemigos[i].destroy();
	}
	conteoSeg = 0;
	jugador.setXPos(3);
}

void JuegoClass::draw()
{
	playableArea.clear();
	//dibujar enemigos
	for (byte i = 0; i < SIZEOF_ENEMIGOS; i++)
	{
		auto& enemy = enemigos[i];
		if (enemy)
		{
			enemy.redraw();
		}
	}
	jugador.redraw();
}
