#include "ConfParams.h"
#include <string.h>

ConfParams::ConfParams(const int & step, const int & minimum, const int & maximum)
	:Step(step)
	,Min(minimum)
	,Max(maximum)
{
	
}

ConfParams::~ConfParams()
{
}

void ConfParams::setLabel(const String & name)
{
	label = name;
}

const String & ConfParams::getLabel()
{
	return label;
}

void ConfParams::changeValue()
{

}

void ConfParams::setValue(const int & valueToSet)
{
	currentValue = valueToSet;
}

const int & ConfParams::getValue()
{
	return currentValue;
}
