#include "HWconfiguration.h"

HWconfiguration::HWconfiguration()
{

}

HWconfiguration::~HWconfiguration()
{

}

const int & HWconfiguration::getNrOfSteps()
{
	return NrOfSteps;
}

const int & HWconfiguration::getFirstStepPin()
{
	return FirstStepPin;
}

const int & HWconfiguration::getPowerSupplierPin()
{
	return PowerSupplierPin;
}

const int & HWconfiguration::getFirstLCDscreenPin()
{
	return FirstLCDscreenPin;
}

const int & HWconfiguration::getSensorDownPin()
{
	return SensorDownPin;
}

const int & HWconfiguration::getSensorUpPin()
{
	return SensorUpPin;
}

const int & HWconfiguration::getPhotoSensorPin()	//analog pin!
{
	return PhotoSensorPin;
}

const int & HWconfiguration::getChangeStateButtonPin()
{
	return ChangeStateButtonPin;
}

const int & HWconfiguration::getSelectButtonPin()
{
	return SelectButtonPin;
}

const int & HWconfiguration::getSetButtonPin()
{
	return SetButtonPin;
}
const int & HWconfiguration::getDimIndicatorPin()
{
	return DimIndicatorPin;
}

const int & HWconfiguration::getDeviceStatusLedPin()
{
	return DeviceStatusLedPin;
}

const int & HWconfiguration::getLcdLedPwrInd()
{
	return LcdLedPwrInd;
}
