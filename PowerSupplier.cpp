// 
// 
// 

#include "PowerSupplier.h"

PowerSupplier::PowerSupplier(const int & pinNr)
	:Pin(pinNr)
{
	pinMode(Pin, OUTPUT);
}

PowerSupplier::~PowerSupplier()
{
}

void PowerSupplier::enable()
{
	if (!activated)
	{
		digitalWrite(Pin, HIGH);
		activated = true;
		delay(100);	//zeby dac mu chwilke na zalaczenie!
	}
}

void PowerSupplier::disable()
{
	digitalWrite(Pin, LOW);
	activated = false;
}
