#include "StatusLed.h"

StatusLed::StatusLed(const int & pinNr)
	:Pin(pinNr)
{
	pinMode(pinNr, OUTPUT);
}

StatusLed::~StatusLed()
{
}

void StatusLed::on()
{
	digitalWrite(Pin, HIGH);
}

void StatusLed::off()
{
	digitalWrite(Pin, LOW);
}
