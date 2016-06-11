#include "Indicator.h"

Indicator::Indicator(const int & pinNr)
	:Pin(pinNr)
{
	pinMode(pinNr, OUTPUT);
}

Indicator::~Indicator()
{
}

void Indicator::on()
{
	digitalWrite(Pin, HIGH);
}

void Indicator::off()
{
	digitalWrite(Pin, LOW);
}


