#include <LiquidCrystal.h>
#include "HWconfiguration.h"
#include "Configuration.h"
#include "Menu.h"
#include "Sensor.h"
#include "PowerSupplier.h"
#include "Indicator.h"
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
Indicator * statusLed;
Indicator * dimIndicator;
Indicator * screenLed;
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
void changeState(const ControllerState state);
void putToConfigurationState();
void putToWorkingState();
void applyChanges();

void wait(const int & illuminationTime); //z zachowaniem responsywnosci

// SETUP
void setup()
{	
	initController();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN LOOP
void loop()
{
	while (ctrlState == ControllerState::Working)
	{		
		if (buttonClicked(hwcfg->getChangeStateButtonPin()))
			changeState(ControllerState::Configuration);
				
		while (sensorDown->isTriggered() || sensorUp->isTriggered())
		{
			powerSupplier->enable();

			while (!lights->isIlluminated())
				turnOnIllumination();
						
			if (lights->isIlluminated())
				break;
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
		if (buttonClicked(hwcfg->getChangeStateButtonPin()))
			changeState(ControllerState::Working);

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

void changeState(const ControllerState state)
{
	lcdScreen->clear();

	if (ctrlState == ControllerState::Working)
		putToConfigurationState();

	if (ctrlState == ControllerState::Configuration)
		putToWorkingState();
				
	ctrlState = state;			
}

void putToConfigurationState()
{
	screenLed->on();
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
	applyChanges();
	screenLed->off();
	statusLed->on();
	lcdScreen->print("Praca!");
	delay(1500);
	lcdScreen->noDisplay();
}

void applyChanges()
{
	lights->changeEnablerDown(conf->getTurnOnMode_Down());
	lights->changeEnablerUp(conf->getTurnOnMode_Up());
	lights->setEnablerDelay(conf->getTurnOnStepDelay());

	lights->changeDisablerDown(conf->getTurnOffMode_Down());
	lights->changeDisablerUp(conf->getTurnOffMode_Up());
	lights->setDisablerDelay(conf->getTurnOffStepDelay());	
}

void turnOnIllumination()
{	
	//trzeba to sprawdzac ze wzgledu na pierwszy if
	sensorDown->isTriggered();
	sensorUp->isTriggered();

	if (sensorDown->wasActivated() && sensorUp->wasActivated())
	{
		lights->turnOnLightsImmediately();
		return;
	}
		
	if (sensorDown->wasActivated())
		lights->turnOnLightsDown();

	if (sensorUp->wasActivated())
		lights->turnOnLightsUp();
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
				lights->turnOnLightsImmediately();
				lights->resetDisablersCounters();
				break;
			}
		}		
	}

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
	statusLed = new Indicator(hwcfg->getDeviceStatusLedPin());
	dimIndicator = new Indicator(hwcfg->getDimIndicatorPin());
	screenLed = new Indicator(hwcfg->getLcdLedPwrInd());
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
