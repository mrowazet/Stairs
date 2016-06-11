// Configuration.h

#ifndef _CONFIGURATION_h
#define _CONFIGURATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Configuration
{
	friend class Menu;

	public:
		Configuration();
		virtual ~Configuration();

		const int & getNrOfOptions() const;

		const int & getTurnOnMode_Down()const;
		const int & getTurnOnMode_Up()const;
		const int & getTurnOnStepDelay()const;
		const int & getTurnOffMode_Down()const;
		const int & getTurnOffMode_Up()const;
		const int & getTurnOffStepDelay()const;
		const int & getLitTime()const;
		const int & getBrightnessThreshold()const;
		const int & getBrightnessOffset()const;

		void setTurnOnMode_Down(const int & v);
		void setTurnOnMode_Up(const int & v);
		void setTurnOnStepDelay(const int & v);
		void setTurnOffMode_Down(const int & v);
		void setTurnOffMode_Up(const int & v);
		void setTurnOffStepDelay(const int & v);
		void setLitTime(const int & v);
		void setBrightnessThreshold(const int & v);
		void setBrightnessOffset(const int & v);


	private:
		//ustawialne
		int turnOnMode_Down = 1;					//tryb
		int turnOnMode_Up = 2;						//tryb
		int turnOnStepDelay = 200;					//delay przy wlaczaniu
		int turnOffMode_Down = 1;					//tryb
		int turnOffMode_Up = 2;						//tryb
		int turnOffStepDelay = 200;					//delay przy wylaczaniu
		int litTime = 3000;							//czas swiecenia po pelnym zapaleniu
		int brightnessThreshold = 200;				//dla zapalania zmierzchowego
		int brightnessOffset = 75;					//np. zapala przy 300, gasi przy 350

		//stale
		const int NrOfOptionsInMenu = 9;			//ilosc opcji
		const int MinDelaySwitchStep = 50;			//min wartosc dla step delay
		const int MaxDelaySwitchStep = 500;			//max wartosc dla step delay
		const int SwitchStep = 50;					//krok dla zmiany step delay
		const int MinLitTime = 2000;				//min czas swiecenia	
		const int MaxLitTime = 10000;				//max czas swiecenia
		const int LitTimeStep = 1000;				//ktok dla zmiany lit time
		const int MinBrightness = 20;				//minimanlna wartosc progu jasnosci
		const int MaxBrightness = 500;				//maxymalna wartosc progu jasnosci
		const int BrightnessStep = 20;				//krok dla zmiany progu jasnosci
		const int MinBrightnessOffset = 50;			//min offset
		const int MaxBrightnessOffset = 250;		//max offset
		const int BrightnessOffsetStep = 25;		//krok dla zmiany offsetu
		const int ModeStep = 1;						//krok dla zmiany trybu
		const int NrOfAvailableModes = 3;			//ilosc trybow dla wl/wyl
};

#endif

