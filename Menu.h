// Menu.h

#ifndef _MENU_h
#define _MENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class LiquidCrystal;
class ConfParam;
class Configuration;

class Menu
{
	public:
		Menu(LiquidCrystal * ptr, Configuration * configuration);
		~Menu();
		void changeOption();
		void changeValue();
		void loadParameters();
		void saveParamaters();
		void resetCurrentOptionIndex();

	protected:
		struct MenuOrder;
		MenuOrder * menuOrder;
		LiquidCrystal * lcd;
		Configuration * conf;
		ConfParam ** menu;
		ConfParam * currentMenuPos;
		int selectedOptionIndex = 0;

		void init();
		void refreshScreen();

		struct MenuOrder
		{
			const int TurnOnMode_Down = 0;
			const int TurnOnMode_Up = 1;
			const int TurnOnStepDelay = 2;
			const int TurnOffMode_Down = 3;
			const int TurnOffMode_Up = 4;
			const int TurnOffStepDelay = 5;
			const int LitTimeDelay = 6;
		};


};

#endif

