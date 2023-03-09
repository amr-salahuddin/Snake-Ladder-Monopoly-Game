#pragma once
#include "Action.h"


class PlayToDesign :public Action
{
public:
	PlayToDesign(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
};

