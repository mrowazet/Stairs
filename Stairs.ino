#include "Lights.h"
#include "Mode.h"

//PARAMETERS
enum class Parameters { nrOfSteps = 5, firstStepPin = 8 };

// GLOBAL
enum class Sensor { Up, Down, NONE };
enum class State { IDLE, BUSY, ON };
enum class Menu { Nothing, TurnOnMode, TurnOnStepDelay, TrunOffMode, TurnOffStepDelay, LitTimeDelay };

Lights * lights;

const int SelectPin = 4;
const int SetPin = 5;
const int SensorDown = 2;
const int SensorUp = 3;

Sensor activatedSensor = Sensor::NONE;
State state = State::IDLE;
Menu selectedMenu = Menu::Nothing;
int litTime = 3000;

// FUNCTION PROTOTYPES
void initSensors();
void initButtons();
int calculateDelayForLitTime(int &wantedTime);

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
	lights->turnOnLights();
	delay(litTime);

	lights->turnOffLights();
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
