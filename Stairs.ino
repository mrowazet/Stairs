#include <LiquidCrystal.h>
#include "DefaultOptionsParams.h"
#include "ConfParams.h"
#include "Sensor.h"
#include "PowerSupplier.h"
#include "StatusLed.h"
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
	nrOfOptionsInMenu = 7,
	nrOfAvailableModes = 3
	
};
enum class Menu
{	
	TurnOnMode_Down, 
	TurnOnMode_Up, 
	TurnOnStepDelay, 
	TurnOffMode_Down, 
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
ConfParams* * options;
LiquidCrystal * lcdScreen;
Sensor * sensorDown;
Sensor * sensorUp;
Lights * lights;
StatusLed * statusLed;
PowerSupplier * powerSupplier;
Menu * selectedMenu;

//VARIABLES
int litTime = 3000; //zostawic jak jest? NIE! klasa z parametrami?
ControllerState ctrlState = ControllerState::Working;

// FUNCTION PROTOTYPES
void initController();
void initMenu();
void initButtons();
void initLcdScreen();

void turnOnIllumination();
void turnOffIllumination();

bool changeState(const ControllerState state);
void setToConfigurationState();
void setToWorkingState();

void wait(const int & illuminationTime); //z zachowaniem responsywnosci

// SETUP
void setup()
{	
	initController();

	//test
	sensorDown->setState(false);
	sensorUp->setState(true);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
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

// FUNCTIONS DEFINITIONS ///////////////////////////////////////////////////////////////////////////
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
				setToConfigurationState();

			if (ctrlState == ControllerState::Configuration)
				setToWorkingState();
				
			ctrlState = state;			
		}

		change = true;
	}

	if (change)
		delay(200);

	return change;
}

void setToConfigurationState()
{
	statusLed->off();
	lights->turnOffLightsImmediately();
	lights->resetEnablersCounters();
	lcdScreen->display();
	lcdScreen->print("Konfiguracja!");



	//test
	delay(2000);
	ConfParams * ptr;
	for (int i = 0; i < (int)CtrlParams::nrOfOptionsInMenu; i++)
	{
		ptr = options[i];
		lcdScreen->clear();
		lcdScreen->print(ptr->getLabel());
		lcdScreen->setCursor(0, 1);
		lcdScreen->print(ptr->getValue());
		delay(2000);
	}
}

void setToWorkingState()
{
	statusLed->on();
	lcdScreen->print("Praca!");
	delay(1800);
	lcdScreen->noDisplay();
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

void initController()
{
	initButtons();
	initLcdScreen();
	initMenu();

	sensorDown = new Sensor((int)CtrlParams::sensorDownPin);
	sensorUp = new Sensor((int)CtrlParams::sensorUpPin);
	lights = new Lights((int)CtrlParams::nrOfSteps, (int)CtrlParams::firstStepPin);
	statusLed = new StatusLed((int)CtrlParams::deviceStatusLedPin);
	powerSupplier = new PowerSupplier((int)CtrlParams::powerSupplierPin);

	statusLed->on();
}

void initButtons()
{
	pinMode((int)CtrlParams::changeStateButtonPin, INPUT_PULLUP);
	pinMode((int)CtrlParams::selectButtonPin, INPUT_PULLUP);
	pinMode((int)CtrlParams::setButtonPin, INPUT_PULLUP);
}

void initLcdScreen()
{
	int startPin = (int)CtrlParams::firstLCDscreenPin;
	lcdScreen = new LiquidCrystal(startPin, startPin + 1, startPin + 2, startPin + 3, startPin + 4, startPin + 5);
	lcdScreen->begin(16, 2);
	lcdScreen->clear();
}

void initMenu()
{
	DefaultOptionsParams d;
	options = new ConfParams*[(int)CtrlParams::nrOfOptionsInMenu];

	const int NrOfModes = (int)CtrlParams::nrOfAvailableModes;

	int index = (int)Menu::TurnOnMode_Down;
	options[index] = new ConfParams(d.StepMode, 1, NrOfModes);
	options[index]->setLabel("Tryb wl. dol:");
	options[index]->setValue(d.TurnOnMode_Down);

	index = (int)Menu::TurnOnMode_Up;
	options[index] = new ConfParams(d.StepMode, 1, NrOfModes);
	options[index]->setLabel("Tryb wl. gora:");
	options[index]->setValue(d.TurnOnMode_Up);

	index = (int)Menu::TurnOnStepDelay;
	options[index] = new ConfParams(d.StepSwitch, d.MinDelaySwitchStep, d.MaxDelaySwitchStep);
	options[index]->setLabel("Wl. czas kroku:");
	options[index]->setValue(d.TurnOnStepDelay);

	index = (int)Menu::TurnOffMode_Down;
	options[index] = new ConfParams(d.StepMode, 1, NrOfModes);
	options[index]->setLabel("Tryb wyl. dol:");
	options[index]->setValue(d.TurnOffMode_Down);

	index = (int)Menu::TurnOffMode_Up;
	options[index] = new ConfParams(d.StepMode, 1, NrOfModes);
	options[index]->setLabel("Tryb wyl. gora:");
	options[index]->setValue(d.TurnOffMode_Up);

	index = (int)Menu::TurnOffStepDelay;
	options[index] = new ConfParams(d.StepSwitch, d.MinDelaySwitchStep, d.MaxDelaySwitchStep);
	options[index]->setLabel("Wyl. czas kroku:");
	options[index]->setValue(d.TurnOffStepDelay);

	index = (int)Menu::LitTimeDelay;
	options[index] = new ConfParams(d.StepLitTime, d.MinLitTime, d.MaxLitTime);
	options[index]->setLabel("Czas podswietl.:");
	options[index]->setValue(d.LitTime);
}
