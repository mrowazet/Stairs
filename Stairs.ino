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
	setButtonPin = 6,
	defaultLitTime = 3000
};

// GLOBAL
enum class Menu 
{	
	Nothing, 
	TurnOnMode_Down, 
	TurnOnMode_Up, 
	TurnOnStepDelay, 
	TrunOffMode_Down, 
	TurnOffMode_Up, 
	TurnOffStepDelay, 
	LitTimeDelay 
};
						
//POINTERS
Sensor * sensorDown;
Sensor * sensorUp;
Lights * lights;
PowerSupplier * powerSupplier;

Menu selectedMenu = Menu::Nothing;
int litTime = (int)Parameters::defaultLitTime;

// FUNCTION PROTOTYPES
void turnOffIllumination();

// SETUP
void setup()
{	
	sensorDown = new Sensor((int)Parameters::sensorDownPin);
	sensorUp = new Sensor((int)Parameters::sensorUpPin);
	lights = new Lights((int)Parameters::nrOfSteps, (int)Parameters::firstStepPin);
	powerSupplier = new PowerSupplier((int)Parameters::powerSupplierPin);

	//test
	sensorDown->setState(false);
	sensorUp->setState(true);
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
		lights->turnOnLightsDown();
		sensorDown->setActivated(true);
	}

	if (sensorUp->isTriggered())
	{
		lights->turnOnLightsUp();
		sensorUp->setActivated(true);
	}

	if (lights->isIlluminated())
	{
		int time = 0;
		do
		{
			time += 100;
			delay(100);

			//if (sensorDown->isTriggered() || sensorUp->isTriggered())
				//time = 0;

		} while (time < litTime);
		
		turnOffIllumination();		
	}
		
}

// FUNCTIONS DEFINITIONS ///////////////////////////////////////
void turnOffIllumination()
{
	if (sensorDown->wasActivated() && sensorUp->wasActivated())
		lights->turnOffLightsImmediately();	
	else
	{
		if (sensorDown->wasActivated())
			lights->turnOffLightsDown();
		if (sensorUp->wasActivated())
			lights->turnOffLightsUp();
	}

	powerSupplier->disable();
	lights->resetEnablersCounters();
	sensorDown->setActivated(false);
	sensorUp->setActivated(false);

	//test
	delay(3000);
}
