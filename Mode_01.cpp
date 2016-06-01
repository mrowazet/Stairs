#include "Mode_01.h"

Mode_01::Mode_01(int * stepsPtr, const int size)
	:Mode(stepsPtr, size)
{
}

void Mode_01::turnOn()
{
	digitalWrite(steps[stepNr], HIGH);
	delay(stepDelay);

	stepNr++;

	if (stepNr == tabSize)
		stepNr = 0;
	
}

void Mode_01::turnOff()
{
	//for (int i = 0; i < tabSize; i++)
	//{
		digitalWrite(steps[stepNr], LOW);
		delay(stepDelay);

		stepNr++;

		if (stepNr == tabSize)
			stepNr = 0;
	//}
}

void Mode_01::clearStepNr()
{
	stepNr = 0;
}

Mode_01::~Mode_01()
{
}
