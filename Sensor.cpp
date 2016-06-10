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
	if (digitalRead(Pin) == HIGH)
	{
		activated = true;
		return true;
	}
		

	return false;
}

const bool & Sensor::wasActivated() const
{
	return activated;
}

void Sensor::setActivated(const bool & state)
{
	activated = state;
}
