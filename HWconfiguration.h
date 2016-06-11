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
		const int & getPhotoSensorPin(); //analog pin!
		const int & getChangeStateButtonPin();
		const int & getSelectButtonPin();
		const int & getSetButtonPin();
		const int & getDimIndicatorPin();
		const int & getDeviceStatusLedPin();
		const int & getLcdLedPwrInd();

	private:
		const int NrOfSteps = 16;

		const int FirstStepPin = 22;
		const int FirstLCDscreenPin = 14;

		const int PhotoSensorPin = 0; //analog pin!
		const int ChangeStateButtonPin = 2;
		const int SelectButtonPin = 3;
		const int SetButtonPin = 4;
		const int LcdLedPwrInd = 10;
		const int DimIndicatorPin = 11;
		const int PowerSupplierPin = 12;
		const int DeviceStatusLedPin = 13;		
		const int SensorDownPin = 20;
		const int SensorUpPin = 21;
		
		
		
		
		
};

#endif

