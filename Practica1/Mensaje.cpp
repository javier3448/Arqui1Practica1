#include "Mensaje.h"
#include "PlayableArea.h"
#include "Definiciones.h"

MensajeClass::MensajeClass() {

}

void MensajeClass::bajar() {
	for (int i = 0; i < SIZE_OF_MESSAGE; i++) {
		POSICIONES[i]++;
		if (POSICIONES[i] == 16) {
			POSICIONES[i] = -192;
		}
		playableArea.drawOnes(0, POSICIONES[i], alfabeto[secuencia[i]], SIZEOF_MYCHAR);
	}

}

void MensajeClass::subir() {
	for (int i = 0; i < SIZE_OF_MESSAGE; i++) {
		POSICIONES[i]--;
		if (POSICIONES[i] == -192) {//>=
			POSICIONES[i] = 16;
		}
		playableArea.drawOnes(0, POSICIONES[i], alfabeto[secuencia[i]], SIZEOF_MYCHAR);
	}

}

bool lastSwitchState = 1;
void MensajeClass::mover(int sn) {
	
	if (lastSwitchState != sn)
	{
		auxMensaje = 0;
		lastSwitchState = sn;
	}

	switch (sn)
	{
	case 1:
		playableArea.clear();
		bajar();
		break;
	case 0:
		playableArea.clear();
		subir();
		break;
	}
	auxMensaje = 0;
}

void MensajeClass::setUp(long v, char s)
{

	if (v >= 0 && v <= 255) {//Slow
		if (auxMensaje >= 35) {
			mover(s);
		}
	}
	else if (v >= 256 && v <= 511) {//Normal
		if (auxMensaje >= 20) {
			mover(s);
		}
	}
	else if (v >= 512 && v <= 768) {//Fast
		if (auxMensaje >= 10) {
			mover(s);
		}
	}
	else {//Very fast
		if (auxMensaje >= 5) {
			mover(s);
		}
	}
}


void MensajeClass::prueba() {

	if (auxMensaje > 100) {
		playableArea.clear();
		POSICIONES[0]++;
		playableArea.drawOnes(0, POSICIONES[0], alfabeto[1], SIZEOF_MYCHAR);
		auxMensaje = 0;
	}
}


