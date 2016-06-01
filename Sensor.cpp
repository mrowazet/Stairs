// 
// 
// 

#include "Sensor.h"

Sensor::Sensor(const int & pinNr)
	:Pin(pinNr)
{
	pinMode(Pin, INPUT);
}

Sensor::~Sensor()
{
}

bool Sensor::isTriggered()
{	
	//odczytac stan!
	//if (digitalRead(Pin) == HIGH)
	//	return true;

	//return false;

	return state;
}

const bool & Sensor::wasActivated() const
{
	return activated;
}

void Sensor::setActivated(const bool & state)
{
	activated = state;
}

//test
void Sensor::setState(bool s)
{
	state = s;
}
