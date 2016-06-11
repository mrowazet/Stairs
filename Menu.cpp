#include "Menu.h"
#include <LiquidCrystal.h>
#include "Configuration.h"
#include "ConfParam.h"

Menu::Menu(LiquidCrystal * ptr, Configuration * configuration)
	:lcd(ptr)
	,conf(configuration)
{
	init();
}

Menu::~Menu()
{
}

void Menu::changeOption()
{
	selectedOptionIndex++;
	if (selectedOptionIndex == conf->NrOfOptionsInMenu)
		selectedOptionIndex = 0;	

	refreshScreen();
}

void Menu::changeValue()
{
	menu[selectedOptionIndex]->changeValue();
	refreshScreen();
}

void Menu::refreshScreen()
{
	lcd->clear();
	lcd->print(menu[selectedOptionIndex]->getLabel());
	lcd->setCursor(0, 1);
	lcd->print(menu[selectedOptionIndex]->getValue());
}

void Menu::loadParameters()
{
	menu[menuOrder->TurnOnMode_Down]->setValue(conf->getTurnOnMode_Down());
	menu[menuOrder->TurnOnMode_Up]->setValue(conf->getTurnOnMode_Up());
	menu[menuOrder->TurnOnStepDelay]->setValue(conf->getTurnOnStepDelay());
	menu[menuOrder->TurnOffMode_Down]->setValue(conf->getTurnOffMode_Down());
	menu[menuOrder->TurnOffMode_Up]->setValue(conf->getTurnOffMode_Up());
	menu[menuOrder->TurnOffStepDelay]->setValue(conf->getTurnOffStepDelay());
	menu[menuOrder->LitTimeDelay]->setValue(conf->getLitTime());
	menu[menuOrder->BrightnessThreshold]->setValue(conf->getBrightnessThreshold());
	menu[menuOrder->BrightnessOffset]->setValue(conf->getBrightnessOffset());
}

void Menu::saveParamaters()
{
	conf->setTurnOnMode_Down(menu[menuOrder->TurnOnMode_Down]->getValue());
	conf->setTurnOnMode_Up(menu[menuOrder->TurnOnMode_Up]->getValue());
	conf->setTurnOnStepDelay(menu[menuOrder->TurnOnStepDelay]->getValue());
	conf->setTurnOffMode_Down(menu[menuOrder->TurnOffMode_Down]->getValue());
	conf->setTurnOffMode_Up(menu[menuOrder->TurnOffMode_Up]->getValue());
	conf->setTurnOffStepDelay(menu[menuOrder->TurnOffStepDelay]->getValue());
	conf->setLitTime(menu[menuOrder->LitTimeDelay]->getValue());
	conf->setBrightnessThreshold(menu[menuOrder->BrightnessThreshold]->getValue());
	conf->setBrightnessOffset(menu[menuOrder->BrightnessOffset]->getValue());
}

void Menu::init()
{
	menuOrder = new MenuOrder();
	menu = new ConfParam*[conf->NrOfOptionsInMenu];

	const int NrOfModes = conf->NrOfAvailableModes;

	int index = menuOrder->TurnOnMode_Down;
	menu[index] = new ConfParam(conf->ModeStep, 1, NrOfModes);
	menu[index]->setLabel("Tryb wl. dol:");
	menu[index]->setValue(conf->turnOnMode_Down);

	index = menuOrder->TurnOnMode_Up;
	menu[index] = new ConfParam(conf->ModeStep, 1, NrOfModes);
	menu[index]->setLabel("Tryb wl. gora:");
	menu[index]->setValue(conf->turnOnMode_Up);

	index = menuOrder->TurnOnStepDelay;
	menu[index] = new ConfParam(conf->SwitchStep, conf->MinDelaySwitchStep, conf->MaxDelaySwitchStep);
	menu[index]->setLabel("Wl. czas kroku:");
	menu[index]->setValue(conf->turnOnStepDelay);

	index = menuOrder->TurnOffMode_Down;
	menu[index] = new ConfParam(conf->ModeStep, 1, NrOfModes);
	menu[index]->setLabel("Tryb wyl. dol:");
	menu[index]->setValue(conf->turnOffMode_Down);

	index = menuOrder->TurnOffMode_Up;
	menu[index] = new ConfParam(conf->ModeStep, 1, NrOfModes);
	menu[index]->setLabel("Tryb wyl. gora:");
	menu[index]->setValue(conf->turnOffMode_Up);

	index = menuOrder->TurnOffStepDelay;
	menu[index] = new ConfParam(conf->SwitchStep, conf->MinDelaySwitchStep, conf->MaxDelaySwitchStep);
	menu[index]->setLabel("Wyl. czas kroku:");
	menu[index]->setValue(conf->turnOffStepDelay);

	index = menuOrder->LitTimeDelay;
	menu[index] = new ConfParam(conf->LitTimeStep, conf->MinLitTime, conf->MaxLitTime);
	menu[index]->setLabel("Czas podswietl.:");
	menu[index]->setValue(conf->litTime);

	index = menuOrder->BrightnessThreshold;
	menu[index] = new ConfParam(conf->BrightnessStep, conf->MinBrightness, conf->MaxBrightness);
	menu[index]->setLabel("Zmierzch:");
	menu[index]->setValue(conf->brightnessThreshold);

	index = menuOrder->BrightnessOffset;
	menu[index] = new ConfParam(conf->BrightnessOffsetStep, conf->MinBrightnessOffset, conf->MaxBrightnessOffset);
	menu[index]->setLabel("Zm. offset:");
	menu[index]->setValue(conf->brightnessOffset);
}

void Menu::resetCurrentOptionIndex()
{
	selectedOptionIndex = 0;
}