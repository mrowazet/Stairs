// Sensor.h

#ifndef _SENSOR_h
#define _SENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Sensor
{
	public:
		Sensor(const int & pinNr, bool downLocation);
		~Sensor();

		bool isTriggered();

		//dla sprawdzenia, ktory odpalil sekwencje
		const bool & isActivated() const;
		void setActivated(const bool & state);
		const bool & isDownstairs();

		//test
		void setState(bool s);

	private:
		bool activated = false;
		const bool LocatedDownstairs;
		const int Pin;

		//test
		bool state;
};


#endif

