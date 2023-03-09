#pragma once
#include "Action.h"


class DesignToPlay :public Action
{
public:
	DesignToPlay(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
};

