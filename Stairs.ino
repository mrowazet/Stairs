#include <LiquidCrystal.h>
#include "HWconfiguration.h"
#include "Configuration.h"
#include "Menu.h"
#include "Sensor.h"
#include "PowerSupplier.h"
#include "StatusLed.h"
#include "Lights.h"
#include "Mode.h"

//GLOBAL
enum class ControllerState { Configuration, Working };
						
//POINTERS
HWconfiguration * hwcfg;
Configuration * conf;
LiquidCrystal * lcdScreen;
Sensor * sensorDown;
Sensor * sensorUp;
Lights * lights;
StatusLed * statusLed;
PowerSupplier * powerSupplier;
Menu * menu;

//VARIABLES
ControllerState ctrlState = ControllerState::Working;

// FUNCTION PROTOTYPES
void initController();
void initButtons();
void initLcdScreen();

void turnOnIllumination();
void turnOffIllumination();

bool buttonClicked(const int & buttonPin);

bool changeState(const ControllerState state);
void putToConfigurationState();
void putToWorkingState();

void wait(const int & illuminationTime); //z zachowaniem responsywnosci

// SETUP
void setup()
{	
	initController();

	//test
	//sensorDown->setState(false);
	//sensorUp->setState(true);
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
			wait(conf->getLitTime());
			turnOffIllumination();
			powerSupplier->disable();
		}
	}//end of while Working


	while (ctrlState == ControllerState::Configuration)
	{
		if (changeState(ControllerState::Working))
			break;

		if (buttonClicked(hwcfg->getSelectButtonPin()))
			menu->changeOption();

		if (buttonClicked(hwcfg->getSetButtonPin()))
			menu->changeValue();
		
	}//end of while Configuration
}

// FUNCTIONS DEFINITIONS ///////////////////////////////////////////////////////////////////////////
bool buttonClicked(const int & buttonPin)
{
	bool change = false;
	while (digitalRead(buttonPin) == LOW)
		change = true;

	if (change)
		delay(200);

	return change;
}

bool changeState(const ControllerState state)
{
	bool change = false;
	bool notExecuted = true;
	while (digitalRead(hwcfg->getChangeStateButtonPin()) == LOW)
	{
		if (notExecuted)
		{
			lcdScreen->clear();
			notExecuted = false;

			if (ctrlState == ControllerState::Working)
				putToConfigurationState();

			if (ctrlState == ControllerState::Configuration)
				putToWorkingState();
				
			ctrlState = state;			
		}

		change = true;
	}

	if (change)
		delay(200);

	return change;
}

void putToConfigurationState()
{
	statusLed->off();
	lights->turnOffLightsImmediately();
	lights->resetEnablersCounters();
	lcdScreen->display();
	lcdScreen->print("Konfiguracja!");
	menu->loadParameters();
	delay(1500);
	menu->refreshScreen();
}

void putToWorkingState()
{
	menu->resetCurrentOptionIndex();
	menu->saveParamaters();
	statusLed->on();
	lcdScreen->print("Praca!");
	delay(1500);
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

			if (sensorDown->isTriggered() || sensorUp->isTriggered())
			{
				//tylko break moze?
				//albo
				//lights->turnOnLightsImmediately();
				//break;
			}
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

		if (sensorDown->isTriggered() || sensorUp->isTriggered())
			time = 0;

	} while (time < illuminationTime);
}

void initController()
{
	hwcfg = new HWconfiguration();

	initButtons();
	initLcdScreen();

	conf = new Configuration();	
	menu = new Menu(lcdScreen, conf);
	sensorDown = new Sensor(hwcfg->getSensorDownPin());
	sensorUp = new Sensor(hwcfg->getSensorUpPin());
	lights = new Lights(hwcfg->getNrOfSteps(), hwcfg->getFirstStepPin());
	statusLed = new StatusLed(hwcfg->getDeviceStatusLedPin());
	powerSupplier = new PowerSupplier(hwcfg->getPowerSupplierPin());

	statusLed->on();
}

void initButtons()
{
	pinMode(hwcfg->getChangeStateButtonPin(), INPUT_PULLUP);
	pinMode(hwcfg->getSelectButtonPin(), INPUT_PULLUP);
	pinMode(hwcfg->getSetButtonPin(), INPUT_PULLUP);
}

void initLcdScreen()
{
	int startPin = hwcfg->getFirstLCDscreenPin();
	lcdScreen = new LiquidCrystal(startPin, startPin + 1, startPin + 2, startPin + 3, startPin + 4, startPin + 5);
	lcdScreen->begin(16, 2);
	lcdScreen->clear();
}
