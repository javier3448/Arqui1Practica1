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

	//Spawner:
	if (enemy.isNull) 
	{
		enemy = EnemigoClass(random(0, sizeof(playableArea.gameArray[0]) * 8 - 2), -1);
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
	return true;
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

void JuegoClass::pause()
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
}

void JuegoClass::draw()
{
	playableArea.clear();
	//dibujar enemigos
	if (!enemy.isNull)
	{
		enemy.redraw();
	}
	jugador.redraw();
}
