#pragma once
#include"Action.h"
#include"CellPosition.h"
#include"Cell.h"
//Added class
class CutCardAction :public Action
{
	CellPosition CardCell;  //cell supposed to contain a card
public:
	CutCardAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads CutCardAction action parameters (cardNumber, cardPosition)

	virtual void Execute(); // Creates a new Card Object of the specific Card Number
							// and Reads the Parameters of This Card Number (if any)
							// then Sets this Card Object to GameObject Pointer of its Cell

	virtual ~CutCardAction(); // A Virtual Destructor
};

