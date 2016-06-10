#include "ConfParam.h"
#include <string.h>

ConfParam::ConfParam(const int & step, const int & minimum, const int & maximum)
	:Step(step)
	,Min(minimum)
	,Max(maximum)
{
	
}

ConfParam::~ConfParam()
{
}

void ConfParam::setLabel(const String & name)
{
	label = name;
}

const String & ConfParam::getLabel()
{
	return label;
}

void ConfParam::changeValue()
{
	currentValue += Step;

	if (currentValue > Max)
		currentValue = Min;
}

void ConfParam::setValue(const int & valueToSet)
{
	currentValue = valueToSet;
}

const int & ConfParam::getValue()
{
	return currentValue;
}
