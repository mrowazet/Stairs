// PhotoSensor.h

#ifndef _PHOTOSENSOR_h
#define _PHOTOSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class PhotoSensor
{
	public:
		PhotoSensor(const int & pinNr);
		~PhotoSensor();
		const volatile int & getBrightnessValue();

	private:
		const int Pin;
		volatile int val;
};

#endif

