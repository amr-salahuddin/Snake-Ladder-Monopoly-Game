#pragma once
#include"Action.h"
//Added class
class NewGameAction:public Action
{
public:
	NewGameAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads NewGameAction action parameters (startPos, endPos)

	virtual void Execute(); // Creates a new Snake Object 
							// then Sets this Snake object to the GameObject Pointer of its Cell


	virtual ~NewGameAction(); // Virtual Destructor
};

