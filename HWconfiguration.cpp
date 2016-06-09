#include "HWconfiguration.h"

HWconfiguration::HWconfiguration()
{

}

HWconfiguration::~HWconfiguration()
{

}

const int & HWconfiguration::getNrOfSteps()
{
	return nrOfSteps;
}

const int & HWconfiguration::getFirstStepPin()
{
	return firstStepPin;
}

const int & HWconfiguration::getPowerSupplierPin()
{
	return powerSupplierPin;
}

const int & HWconfiguration::getFirstLCDscreenPin()
{
	return firstLCDscreenPin;
}

const int & HWconfiguration::getSensorDownPin()
{
	return sensorDownPin;
}

const int & HWconfiguration::getSensorUpPin()
{
	return sensorUpPin;
}

const int & HWconfiguration::getSensorLightPin()	//analog pin!
{
	return sensorLightPin;
}

const int & HWconfiguration::getChangeStateButtonPin()
{
	return changeStateButtonPin;
}

const int & HWconfiguration::getSelectButtonPin()
{
	return selectButtonPin;
}

const int & HWconfiguration::getSetButtonPin()
{
	return setButtonPin;
}
const int & HWconfiguration::getDimIndicatorPin()
{
	return dimIndicatorPin;
}

const int & HWconfiguration::getDeviceStatusLedPin()
{
	return deviceStatusLedPin;
}
