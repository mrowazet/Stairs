#include "PhotoSensor.h"

PhotoSensor::PhotoSensor(const int & pinNr)
	:Pin(pinNr)
{
	pinMode(Pin, INPUT);
}

PhotoSensor::~PhotoSensor()
{
}

const volatile int & PhotoSensor::getBrightnessValue()
{
	val = analogRead(Pin);
	return val;
}