// HWconfiguration.h

#ifndef _HWCONFIGURATION_h
#define _HWCONFIGURATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class HWconfiguration
{
	public:
		HWconfiguration();
		~HWconfiguration();

		const int & getNrOfSteps();
		const int & getFirstStepPin();
		const int & getPowerSupplierPin();
		const int & getFirstLCDscreenPin();
		const int & getSensorDownPin();
		const int & getSensorUpPin();
		const int & getSensorLightPin(); //analog pin!
		const int & getChangeStateButtonPin();
		const int & getSelectButtonPin();
		const int & getSetButtonPin();
		const int & getDimIndicatorPin();
		const int & getDeviceStatusLedPin();

	private:
		const int nrOfSteps = 16;
		const int firstStepPin = 22;
		const int powerSupplierPin = 11;
		const int firstLCDscreenPin = 14;
		const int sensorDownPin = 20;
		const int sensorUpPin = 21;
		const int sensorLightPin = 0; //analog pin!
		const int changeStateButtonPin = 2;
		const int selectButtonPin = 3;
		const int setButtonPin = 4;
		const int dimIndicatorPin = 12;
		const int deviceStatusLedPin = 13;
};

#endif

