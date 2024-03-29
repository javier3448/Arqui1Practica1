/*
 Name:		Practica1.ino
 Created:	2/6/2020 3:26:25 PM
 Author:	Alvarez
*/

//No necesitamos PISO. Solo SIPO
#include "Enemigo.h"
#include "Juego.h"
#include "Definiciones.h"
#include "PlayableArea.h"
#include "Max7219Driver.h"
#include "Sipo3.h"
#include "Definiciones.h"
#include "Juego.h"
#include "Mensaje.h"

Max7219Driver driverP1 = Max7219Driver(53);
Sipo3 driverP2 = Sipo3(7, 6, 5, LSBFIRST, 2);
JuegoClass juego = JuegoClass();
MensajeClass mensaje = MensajeClass();

// the setup function runs once when you press reset or power the board
const byte PIN_BTN_IZQ = 2;
const byte PIN_BTN_DER = 3;
const byte PIN_BTN_START = 4;
const byte PIN_POT = A5;
const byte PIN_SWITCH = 8;

void setup() {
    randomSeed(analogRead(A0));
    //Set up botones:
    pinMode(PIN_BTN_IZQ, INPUT_PULLUP);
    pinMode(PIN_BTN_DER, INPUT_PULLUP);
    pinMode(PIN_BTN_START, INPUT_PULLUP);
    pinMode(PIN_SWITCH, INPUT_PULLUP);
    DDRC = 0xff;
    DDRA = 0Xff;
    playableArea.clear();
	if (digitalRead(PIN_SWITCH) == HIGH) {
		inPosAbajo();
	}
	else {
		inPosArriba();
	}
}


// the loop function runs over and over again until power down or reset
void loop() {
    static byte loopCount = 0;
    updatePantalla();
    if (loopCount >= 8) {
        loopCount = 0;
        updateEstados();
    }
    loopCount++;
}

//inicializan en vector de posiciones  del mensaje dependiendo de la lectura del switch
void inPosArriba() {
	int inPos = 0;
	for (int i = 0; i < SIZE_OF_MESSAGE; i++) {
		inPos = inPos - 8;
		POSICIONES[i] = inPos;
	}
}

void inPosAbajo() {
	int inPos = 8;
	for (int i = 0; i < SIZE_OF_MESSAGE; i++) {
		inPos = inPos + 8;
		POSICIONES[i] = inPos;
		//Serial.println(POSICIONES[i]);
	}
}

//Actualiza ambas pantallas, 
void updatePantalla()
{
    static byte updatePantallaCount = 0;
    static byte p2Data[2];
    
    //Actualizar la pantalla 2
    PORTA = ~(1 << updatePantallaCount);//el bit en 0 sera la fila que se multiplexara en esta corrida
    PORTC = playableArea.gameArray[updatePantallaCount];

    //Actualiza la pantalla 1
    driverP1.setRow(updatePantallaCount, playableArea.gameArray[(GAME_ARRAY_SIZE - 2) - updatePantallaCount]);//Invierte la segunda pantalla para que se pueda ver mejor en el protoboard que ya esta hecho

    updatePantallaCount++;
    updatePantallaCount &= 0b111;
    delayMicroseconds(750);
}

const byte S_MENSAJE = 0;
const byte S_HOLD_INICIO = 1; //estado entre mensaje y conteo
const byte S_CONTEO = 2;
const byte S_JUEGO = 3;
const byte S_HOLD_PAUSA = 4;
const byte S_PAUSA = 5;
const byte S_GAME_OVER = 6;

byte estadoActual = 0;

//Seria conveniente poner toda la logica de los botones e inputs en otra clase
bool isStartPressed = false;
bool isLeftPressed = false;
bool isRightPressed = false;
bool wasStartPressed = false;
bool wasLeftPressed = false;
bool wasRightPressed = false;

unsigned long holdInicial = 0;//Sirve para ambos estados hold. indica cuando empezo

//Por ahora no estan programadas la funciones para conseguir los input de los botones
void updateEstados() {
    updateInput();
    switch (estadoActual)
    {
    case S_MENSAJE:
        //Codigo para manejar estado: S_MENSAJE
        //velocidadMensaje = analogRead(A5);
        mensaje.setUp(analogRead(PIN_POT), !digitalRead(PIN_SWITCH)); //TODO
		if (isStartPressed && !wasStartPressed)
        {
            holdInicial = millis();
            estadoActual = S_HOLD_INICIO;
        }
		auxMensaje++;
        break;
    case S_HOLD_INICIO:
        //Codigo para manejar estado: S_HOLD_INICIO
        //mensaje.update(analogRead(PIN_POT), !digitalRead(PIN_SWITCH));
        if (millis() - holdInicial >= 3000) 
        {
            holdInicial = 0;
            playableArea.clear();
            estadoActual = S_CONTEO;
            break;
        }
        if (!isStartPressed && !wasStartPressed)
        {
            estadoActual = S_MENSAJE;
        }
        //Continuar en el estado hasta que pasen 3 segundos, luego ir a conteo
        break;
    case S_CONTEO:
        //Codigo para manejar estado: S_CONTEO
        static char numero = ALF_CERO + 3;
        if (millis() - holdInicial >= 1000)
        {
            holdInicial = millis();
            if (numero <= ALF_CERO) {
                numero = ALF_CERO + 3;
                juego.draw();
                estadoActual = S_JUEGO;
                break;
            }
            playableArea.draw(0, 5, alfabeto[numero], SIZEOF_MYCHAR);
            numero = numero - 1;
        }
        //Continuar en el estado hasta que pasen 3 segundos luego ir a juego
        break;
    case S_JUEGO:
        //Codigo para manejar estado: S_JUEGO
        if (isStartPressed && !wasStartPressed) 
        {
            holdInicial = millis();
            playableArea.clear();
            juego.paintSegs = true;
            estadoActual = S_HOLD_PAUSA;
            break;
        }
        //Juego
        if (!juego.tryUpdate(isLeftPressed, wasLeftPressed, isRightPressed, wasRightPressed)) {
            playableArea.clear();
            juego.paintSegs = true;
            estadoActual = S_GAME_OVER;
            break;
        }
        break;
    case S_HOLD_PAUSA:
        //Codigo para manejar estado: S_PAUSA
        juego.pauseAndPrintScore();
        //juego.pause(); Le dice al juego que haga el render de pause();
        if (!isStartPressed && !wasStartPressed)
        {
            estadoActual = S_PAUSA;
            break;
        }
        if (millis() - holdInicial >= 3000) 
        {
            playableArea.clear();
            juego.reset();
            estadoActual = S_MENSAJE;
            break;
        }
        //Continuar en el estado hasta que pasen 3 segundos, luego ir a mensaje
        break;
    case S_PAUSA:
        //juego.pause(); Le dice al juego que haga el render de pause();
        juego.pauseAndPrintScore();
        if (isStartPressed && !wasStartPressed)
        {
            playableArea.clear();
            estadoActual = S_CONTEO;
            break;
        }
        break;
    case S_GAME_OVER:
        //Codigo para manejar estado: S_GAME_OVER
        //juego.gameOver(); Le dice al juego que haga el render de gameOver();
        juego.pauseAndPrintScore();
        if (isStartPressed && !wasStartPressed) 
        {
            playableArea.clear();
            juego.reset();
            estadoActual = S_MENSAJE;
            break;
        }
        break;
    default:
        break;
    }
}

void updateInput() {
    //Primero seteamos los wasPressed porque necesitamos que isPressed y wasPressed sean verdadero y falso respectivamente
    //en al menos una llamada de este metodo
    wasStartPressed = isStartPressed;
    wasLeftPressed = isLeftPressed;
    wasRightPressed = isRightPressed;

    isStartPressed = !digitalRead(PIN_BTN_START);
    isLeftPressed = !digitalRead(PIN_BTN_IZQ);
    isRightPressed = !digitalRead(PIN_BTN_DER);
}