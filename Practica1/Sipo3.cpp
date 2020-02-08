// 
// 
// 

#include "Sipo3.h"


Sipo3::Sipo3(int dataPin, int srlClkPin, int rClkPin, int bitOrder, int numDevices) :
	DATA_PIN(dataPin), SCLK_PIN(srlClkPin), RCLK_PIN(rClkPin), BIT_ORDER(bitOrder), NUM_DEVICES(numDevices)
{
	begin();
	clear();
}

void Sipo3::begin()
{
	pinMode(DATA_PIN, OUTPUT);
	pinMode(SCLK_PIN, OUTPUT);
	pinMode(RCLK_PIN, OUTPUT);
}

void Sipo3::clear()
{
	byte* d = new byte[NUM_DEVICES];
	for (int i = 0; i < NUM_DEVICES; i++)
	{
		d[i] = 0;
	}
	send(d);
	delete[] d;
}

void Sipo3::send(byte* values)
{
	if (sizeof(values) < NUM_DEVICES)
		return;

	digitalWrite(RCLK_PIN, LOW);
	for (int i = NUM_DEVICES - 1; i > -1; i--)
	{
		shiftOut(DATA_PIN, SCLK_PIN, BIT_ORDER, values[i]);
	}
	digitalWrite(RCLK_PIN, HIGH);
}

void Sipo3::end()
{
	clear();
}

