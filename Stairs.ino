#include "Lights.h"
#include "Mode.h"

//PARAMETERS
enum class Parameters { nrOfSteps = 5, firstStepPin = 8 };

//CONSTANTS
const int SensorDown = 2;
const int SensorUp = 3;
const int SensorLight = 4;
const int SelectPin = 5;
const int SetPin = 6;
const int PowerSupplier = 13;

const bool SensorDownstairs = true;
const bool SensorUpstairs = false;

// GLOBAL
enum class State { IDLE, BUSY, ON };
enum class Menu { Nothing, TurnOnMode, TurnOnStepDelay, TrunOffMode, TurnOffStepDelay, LitTimeDelay };

Lights * lights;

//test
bool dol = true;
bool gora = false;

bool sensorDownActivated = false;
bool sensorUpActivated = false;
bool powerSupplierActivated = false;

///

State state = State::IDLE;
Menu selectedMenu = Menu::Nothing;
int litTime = 3000;

// FUNCTION PROTOTYPES
void initSensors();
void initButtons();
void enablePowerSupplier();
void disablePowerSupplier();
int calculateDelayForLitTime(int &wantedTime);
void turnOffIllumination();

// SETUP
void setup()
{
	pinMode(PowerSupplier, OUTPUT);
	initSensors();
	initButtons();
	lights = new Lights((int)Parameters::nrOfSteps, (int)Parameters::firstStepPin);
}

// MAIN LOOP
void loop()
{
	if (dol || gora)
		enablePowerSupplier();

	if (dol && gora)
		lights->turnOnLightsImmediately();

	if (dol)
	{
		lights->turnOnLights(SensorDownstairs);
		state = State::BUSY;
		sensorDownActivated = true;
	}

	if (gora)
	{
		lights->turnOnLights(SensorUpstairs);
		state = State::BUSY;
		sensorUpActivated = true;
	}

	if (lights->isIlluminated())
	{
		delay(litTime);
		turnOffIllumination();		
	}
		
}

// FUNCTIONS DEFINITIONS ///////////////////////////////////////
void initSensors()
{
	pinMode(SensorUp, INPUT_PULLUP);
	pinMode(SensorDown, INPUT_PULLUP);
}

void initButtons()
{
	pinMode(SelectPin, INPUT_PULLUP);
	pinMode(SetPin, INPUT_PULLUP);
}

int calculateDelayForLitTime(int &wantedTime)
{
}

void turnOffIllumination()
{
	if (sensorDownActivated && sensorUpActivated)
		lights->turnOffLightsImmediately();	
	else
	{
		if (sensorDownActivated)
			lights->turnOffLights(SensorDownstairs);
		if (sensorUpActivated)
			lights->turnOffLights(SensorUpstairs);
	}

	disablePowerSupplier();
	lights->resetEnablersCounters();
	sensorDownActivated = false;
	sensorUpActivated = false;

	//test
	delay(3000);
}

void enablePowerSupplier()
{
	if (powerSupplierActivated == false)
	{
		digitalWrite(PowerSupplier, HIGH);
		delay(100);	//zeby dac mu chwilke na zalaczenie!
	}
}

void disablePowerSupplier()
{
	digitalWrite(PowerSupplier, LOW);
}
