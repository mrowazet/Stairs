// PowerSupplier.h

#ifndef _POWERSUPPLIER_h
#define _POWERSUPPLIER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class PowerSupplier
{
	public:
		PowerSupplier(int pinNr);
		~PowerSupplier();

		void enable();
		void disable();

	private:
		const int Pin;
		bool activated = false;
};

#endif

