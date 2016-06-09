#ifndef _CONFPARAM_h
#define _CONFPARAM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class ConfParam
{
	public:
		ConfParam(const int & step, const int & minimum, const int & maximum);
		virtual ~ConfParam();
		void setLabel(const String & name);
		const String & getLabel();
		void changeValue();
		void setValue(const int & valueToSet);
		const int & getValue();
		

	protected:
		String label;
		const int Step;
		const int Min;
		const int Max;	
		int currentValue;
		
};

#endif

