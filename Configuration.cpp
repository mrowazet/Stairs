// 
// 
// 

#include "Configuration.h"

Configuration::Configuration()
{
}

Configuration::~Configuration()
{
}

const int & Configuration::getNrOfOptions() const
{
	return NrOfOptionsInMenu;
}

const int & Configuration::getTurnOnMode_Down() const
{
	return turnOnMode_Down;
}

const int & Configuration::getTurnOnMode_Up() const
{
	return turnOnMode_Up;
}

const int & Configuration::getTurnOnStepDelay() const
{
	return turnOnStepDelay;
}

const int & Configuration::getTurnOffMode_Down() const
{
	return turnOffMode_Down;
}

const int & Configuration::getTurnOffMode_Up() const
{
	return turnOffMode_Up;
}

const int & Configuration::getTurnOffStepDelay() const
{
	return turnOffStepDelay;
}

const int & Configuration::getLitTime() const
{
	return litTime;
}

void Configuration::setTurnOnMode_Down(const int & v)
{
	turnOnMode_Down = v;
}

void Configuration::setTurnOnMode_Up(const int & v)
{
	turnOnMode_Up = v;
}

void Configuration::setTurnOnStepDelay(const int & v)
{
	turnOnStepDelay = v;
}

void Configuration::setTurnOffMode_Down(const int & v)
{
	turnOffMode_Down = v;
}

void Configuration::setTurnOffMode_Up(const int & v)
{
	turnOffMode_Up = v;
}

void Configuration::setTurnOffStepDelay(const int & v)
{
	turnOffStepDelay = v;
}

void Configuration::setLitTime(const int & v)
{
	litTime = v;
}
