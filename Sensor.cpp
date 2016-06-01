// 
// 
// 

#include "Sensor.h"

Sensor::Sensor(const int & pinNr, bool downLocation)
	:Pin(pinNr),
	LocatedDownstairs(downLocation)
{
	pinMode(Pin, INPUT);
}

Sensor::~Sensor()
{
}

bool Sensor::isTriggered()
{//odczytac stan!
	return state;
}

const bool & Sensor::isActivated() const
{
	return activated;
}

void Sensor::setActivated(const bool & state)
{
	activated = state;
}

const bool & Sensor::isDownstairs()
{
	return LocatedDownstairs;
}

void Sensor::setState(bool s)
{
	state = s;
}
