#include <LiquidCrystal.h>
#include "Sensor.h"
#include "PowerSupplier.h"
#include "Lights.h"
#include "Mode.h"

//PARAMETERS
enum class Parameters
{
	nrOfSteps = 16,
	firstStepPin = 22,
	powerSupplierPin = 11,
	firstLCDscreenPin = 14,
	sensorDownPin = 20,
	sensorUpPin = 21,
	sensorLightPin = 0, //digital!
	changeStateButtonPin = 2,
	selectButtonPin = 3,
	setButtonPin = 4,	
	dimIndicatorPin = 12,
	deviceStatusPin = 13, 
	defaultLitTime = 3000
};

// GLOBAL
enum class Menu //do wywalenia!
{	
	TurnOnMode_Down, 
	TurnOnMode_Up, 
	TurnOnStepDelay, 
	TrunOffMode_Down, 
	TurnOffMode_Up, 
	TurnOffStepDelay, 
	LitTimeDelay 
};

enum class ControllerState
{
	Configuration,
	Working
};
						
//POINTERS
LiquidCrystal * lcdScreen;
Sensor * sensorDown;
Sensor * sensorUp;
Lights * lights;
PowerSupplier * powerSupplier;
Menu * selectedMenu;

//VARIABLES
int litTime = (int)Parameters::defaultLitTime; //zostawic jak jest?
ControllerState ctrlState = ControllerState::Working;

// FUNCTION PROTOTYPES
void initButtons();
void turnOnIllumination();
void turnOffIllumination();
bool changeState(const ControllerState state);
void wait(const int & illuminationTime); //z zachowaniem responsywnosci

// SETUP
void setup()
{	//test
	lcdScreen = new LiquidCrystal(14, 15, 16, 17, 18, 19);
	lcdScreen->begin(16, 2); 
	lcdScreen->clear();
	lcdScreen->print("working");
	//

	initButtons();
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
	while (ctrlState == ControllerState::Working)
	{		
		if (changeState(ControllerState::Configuration))
			break;
				
		if (sensorDown->isTriggered() || sensorUp->isTriggered())
		{
			powerSupplier->enable();
			turnOnIllumination();
		}
			
		if (lights->isIlluminated())
		{
			wait(litTime);
			turnOffIllumination();
			powerSupplier->disable();
		}
	}//end of while Working

	while (ctrlState == ControllerState::Configuration)
	{
		if (changeState(ControllerState::Working))
			break;
		
			

		

	}//end of while Configuration
}

// FUNCTIONS DEFINITIONS ///////////////////////////////////////
void initButtons()
{
	pinMode((int)Parameters::changeStateButtonPin, INPUT_PULLUP);
	pinMode((int)Parameters::selectButtonPin, INPUT_PULLUP);
	pinMode((int)Parameters::setButtonPin, INPUT_PULLUP);
}

bool changeState(const ControllerState state)
{
	bool change = false;
	int i = 0;
	while (digitalRead((int)Parameters::changeStateButtonPin) == LOW)
	{
		if (i == 0)
		{
			lcdScreen->clear();
			i++;

			if (ctrlState == ControllerState::Working)
			{
				lights->turnOffLightsImmediately();
				lights->resetEnablersCounters();
				lcdScreen->print("Configuration");
			}
				
			if (ctrlState == ControllerState::Configuration)
				lcdScreen->print("Working");

			ctrlState = state;
			
		}

		change = true;
	}

	if (change)
		delay(200);

	return change;
}

void turnOnIllumination()
{
	if (sensorDown->isTriggered() && sensorUp->isTriggered())
	{
		lights->turnOnLightsImmediately();
		sensorDown->setActivated(true);
		sensorUp->setActivated(true);
		return;
	}
		
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
}

void turnOffIllumination()
{
	if (sensorDown->wasActivated() && sensorUp->wasActivated())
		lights->turnOffLightsImmediately();	
	else
	{
		while (!lights->isAnyLightEnabled())
		{
			if (sensorDown->wasActivated())
				lights->turnOffLightsDown();
			if (sensorUp->wasActivated())
				lights->turnOffLightsUp();

			//if (sensorDown->isTriggered() || sensorUp->isTriggered())
			//{
				//tylko break moze?
				//albo
				//lights->turnOnLightsImmediately();
				//break;
			//}
		}		
	}

	//jak zrobi sie break tam wyzej to chyba sie nie powinno wykonac?
	lights->resetEnablersCounters();
	sensorDown->setActivated(false);
	sensorUp->setActivated(false);
}

void wait(const int & illuminationTime)
{
	int time = 0;
	do
	{
		time += 200;
		delay(200);

		//if (sensorDown->isTriggered() || sensorUp->isTriggered())
		//time = 0;

	} while (time < illuminationTime);
}
