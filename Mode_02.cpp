#include "Mode_02.h"

Mode_02::Mode_02(int * stepsPtr, const int size)
	:Mode(stepsPtr, size)
{
	clearStepNr();
}

void Mode_02::turnOn()
{
	stepNr--;

	digitalWrite(steps[stepNr], HIGH);
	delay(stepDelay);
	
	if (stepNr == 0)
		stepNr = tabSize;
}

void Mode_02::turnOff()
{
	stepNr--;
	//for (int i = tabSize -1; i > -1; i--)
	//{
		digitalWrite(steps[stepNr], LOW);
		delay(stepDelay);

		if (stepNr == 0)
			stepNr = tabSize;
	//}
}

void Mode_02::clearStepNr()
{
	stepNr = tabSize;
}

Mode_02::~Mode_02()
{
}
