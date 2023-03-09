#pragma once

#include "Action.h"
//Added class

class OpenGridAction : public Action
{
	string FileName;
public:

	OpenGridAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads OpenGridAction action parameters (startPos, endPos)

	virtual void Execute(); // Creates a new Snake Object 
							// then Sets this Snake object to the GameObject Pointer of its Cell


	virtual ~OpenGridAction(); // Virtual Destructor

};

