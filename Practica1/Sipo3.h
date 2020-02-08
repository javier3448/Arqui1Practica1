// Sipo3.h

#ifndef _SIPO3_h
#define _SIPO3_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Sipo3
{
public:
	const int DATA_PIN;
	const int SCLK_PIN; //serial clk, shifts in data from the data pin
	const int RCLK_PIN; //Latch, clks in the storage register
	const int BIT_ORDER;
	const int NUM_DEVICES;

	Sipo3(int dataPin, int sClkPin, int rClkPin, int bitOrder, int numDevices);

	void begin();

	void clear();//Setea todos los registros storage en 0

	void send(byte* values);

	//Solo setea todos los registros storage en 0, exactamente lo mismo que clear. Esta funcion es bastante util si se estan usando los registros para controlar LEDs
	void end();
};

#endif

