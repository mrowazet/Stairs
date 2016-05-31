#include "Mode.h"

Mode::Mode(int * stepsPtr, const int size)
	:steps(stepsPtr)
	, tabSize(size)
{

}

Mode::~Mode()
{

}

void Mode::setDelay(int ms)
{
	stepDelay = ms;
}
