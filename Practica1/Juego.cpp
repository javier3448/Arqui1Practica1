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
		s = "0" + num;
	}
	byte firstDigit = s[s.length() - 2] - 48 + ALF_CERO;//msd
	byte secondDigit = s[s.length() - 1] - 48 + ALF_CERO;//lsd
	
	playableArea.draw(0, 0, alfabeto[firstDigit], SIZEOF_MYCHAR);
	playableArea.draw(0, 8, alfabeto[secondDigit], SIZEOF_MYCHAR);
}


JuegoClass::JuegoClass()
{
	
}

void JuegoClass::update(bool isLeftPressed, bool wasLeftPressed, bool isRightPressed, bool wasRightPressed)
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
	paintByte(conteoSeg);
}

void JuegoClass::reset()
{
	inicioTiempo = millis();
}
