#ifndef _CONFPARAMS_h
#define _CONFPARAMS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class ConfParams
{
	public:
		ConfParams(const int & step, const int & minimum, const int & maximum);
		virtual ~ConfParams();
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

