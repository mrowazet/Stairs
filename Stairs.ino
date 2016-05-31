#include "Lights.h"
#include "Mode.h"

//PARAMETERS
enum class Parameters { nrOfSteps = 5, firstStepPin = 8 };

//CONSTANTS
const int SelectPin = 4;
const int SetPin = 5;
const int SensorDown = 2;
const int SensorUp = 3;

const bool SensorDownstairs = true;
const bool SensorUpstairs = false;

// GLOBAL
enum class State { IDLE, BUSY, ON };
enum class Menu { Nothing, TurnOnMode, TurnOnStepDelay, TrunOffMode, TurnOffStepDelay, LitTimeDelay };

Lights * lights;

//test
bool dol = true;
bool gora = true;

bool sensorDownActivated = false;
bool sensorUpActivated = false;

///

State state = State::IDLE;
Menu selectedMenu = Menu::Nothing;
int litTime = 1000;

// FUNCTION PROTOTYPES
void initSensors();
void initButtons();
int calculateDelayForLitTime(int &wantedTime);
void turnOffIllumination();

// SETUP
void setup()
{
	initSensors();
	initButtons();
	lights = new Lights((int)Parameters::nrOfSteps, (int)Parameters::firstStepPin);
}

// MAIN LOOP
void loop()
{
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
		//test
		delay(3000);
		turnOffIllumination();
		delay(1000);
		lights->resetEnablersCounters();
		sensorDownActivated = false;
		sensorUpActivated = false;
	}
		
}

// FUNCTIONS DEFINITIONS
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
}
