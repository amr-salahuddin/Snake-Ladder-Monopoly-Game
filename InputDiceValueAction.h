#pragma once
#include "Action.h"
class InputDiceValueAction :public Action
{
	//Input Dice Nymber from the user
	int InputNumber;
public:
	InputDiceValueAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~InputDiceValueAction();
};

