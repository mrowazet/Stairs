#include <LiquidCrystal.h>
#include "Sensor.h"
#include "PowerSupplier.h"
#include "Lights.h"
#include "Mode.h"

//PARAMETERS
enum class CtrlParams
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
	deviceStatusLedPin = 13, 
	defaultLitTime = 3000
};

// GLOBAL
enum class Menu
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
int litTime = (int)CtrlParams::defaultLitTime; //zostawic jak jest?
ControllerState ctrlState = ControllerState::Working;

// FUNCTION PROTOTYPES
void initController();
void initButtons();
void initStatusLed();
void initLcdScreen();

void turnOnIllumination();
void turnOffIllumination();

bool changeState(const ControllerState state);
void wait(const int & illuminationTime); //z zachowaniem responsywnosci

// SETUP
void setup()
{	
	initController();

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
void initController()
{
	initButtons();
	initStatusLed();
	initLcdScreen();



	sensorDown = new Sensor((int)CtrlParams::sensorDownPin);
	sensorUp = new Sensor((int)CtrlParams::sensorUpPin);
	lights = new Lights((int)CtrlParams::nrOfSteps, (int)CtrlParams::firstStepPin);
	powerSupplier = new PowerSupplier((int)CtrlParams::powerSupplierPin);
}

void initButtons()
{
	pinMode((int)CtrlParams::changeStateButtonPin, INPUT_PULLUP);
	pinMode((int)CtrlParams::selectButtonPin, INPUT_PULLUP);
	pinMode((int)CtrlParams::setButtonPin, INPUT_PULLUP);
}

void initStatusLed()
{
	pinMode((int)CtrlParams::deviceStatusLedPin, OUTPUT);
	digitalWrite((int)CtrlParams::deviceStatusLedPin, HIGH);
}

void initLcdScreen()
{
	int startPin = (int)CtrlParams::firstLCDscreenPin;
	lcdScreen = new LiquidCrystal(startPin, startPin + 1, startPin + 2, startPin + 3, startPin + 4, startPin + 5);
	lcdScreen->begin(16, 2);
	lcdScreen->clear();
}

bool changeState(const ControllerState state)
{
	bool change = false;
	int i = 0;
	while (digitalRead((int)CtrlParams::changeStateButtonPin) == LOW)
	{
		if (i == 0)
		{
			lcdScreen->clear();
			i++;

			if (ctrlState == ControllerState::Working)
			{
				digitalWrite((int)CtrlParams::deviceStatusLedPin, LOW);
				lights->turnOffLightsImmediately();
				lights->resetEnablersCounters();
				lcdScreen->display();
				lcdScreen->print("Konfiguracja");
			}

			if (ctrlState == ControllerState::Configuration)
			{
				digitalWrite((int)CtrlParams::deviceStatusLedPin, HIGH);
				lcdScreen->print("Praca!");
				delay(2000);
				lcdScreen->noDisplay();
			}
				
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
