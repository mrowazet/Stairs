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
		Sensor(const int & pinNr);
		~Sensor();

		bool isTriggered();

		//dla sprawdzenia, ktory odpalil sekwencje
		const bool & wasActivated() const;
		void setActivated(const bool & state);

		//test
		void setState(bool s);

	private:
		bool activated = false;
		const int Pin;

		//test
		volatile bool state;
};


#endif

