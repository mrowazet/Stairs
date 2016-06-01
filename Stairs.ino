#include "Sensor.h"
#include "PowerSupplier.h"
#include "Lights.h"
#include "Mode.h"

//PARAMETERS
enum class Parameters
{
	nrOfSteps = 5,
	firstStepPin = 8,
	powerSupplierPin = 13,
	sensorDownPin = 2,
	sensorUpPin = 3,
	sensorLightPin = 4,
	selectButtonPin = 5,
	setButtonPin = 6
};

// GLOBAL
enum class Menu { Nothing, TurnOnMode, TurnOnStepDelay, TrunOffMode, TurnOffStepDelay, LitTimeDelay };
						
//POINTERS
Sensor * sensorDown;
Sensor * sensorUp;
Lights * lights;
PowerSupplier * powerSupplier;

Menu selectedMenu = Menu::Nothing;
int litTime = 3000;

// FUNCTION PROTOTYPES
void turnOffIllumination();

// SETUP
void setup()
{	
	sensorDown = new Sensor((int)Parameters::sensorDownPin, true);
	sensorUp = new Sensor((int)Parameters::sensorUpPin, false);
	lights = new Lights((int)Parameters::nrOfSteps, (int)Parameters::firstStepPin);
	powerSupplier = new PowerSupplier((int)Parameters::powerSupplierPin);

	//test
	sensorDown->setState(true);
	sensorUp->setState(false);
}

// MAIN LOOP
void loop()
{
	if (sensorDown->isTriggered() || sensorUp->isTriggered())
		powerSupplier->enable();

	if (sensorDown->isTriggered() && sensorUp->isTriggered())
		lights->turnOnLightsImmediately();

	if (sensorDown->isTriggered())
	{
		lights->turnOnLights(sensorDown->isDownstairs());
		sensorDown->setActivated(true);
	}

	if (sensorUp->isTriggered())
	{
		lights->turnOnLights(sensorUp->isDownstairs());
		sensorUp->setActivated(true);
	}

	if (lights->isIlluminated())
	{
		delay(litTime);
		turnOffIllumination();		
	}
		
}

// FUNCTIONS DEFINITIONS ///////////////////////////////////////
void turnOffIllumination()
{
	if (sensorDown->isActivated() && sensorUp->isActivated())
		lights->turnOffLightsImmediately();	
	else
	{
		if (sensorDown->isActivated())
			lights->turnOffLights(sensorDown->isDownstairs());
		if (sensorUp->isActivated())
			lights->turnOffLights(sensorUp->isDownstairs());
	}

	powerSupplier->disable();
	lights->resetEnablersCounters();
	sensorDown->setActivated(false);
	sensorUp->setActivated(false);

	//test
	delay(3000);
}
