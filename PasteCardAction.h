#pragma once
#include"Action.h"
#include"CellPosition.h"
#include"Cell.h"
class PasteCardAction :public Action
{
	CellPosition CardCell;  //cell supposed to contain a card
public:
	PasteCardAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads PasteCardAction action parameters (cardNumber, cardPosition)

	virtual void Execute(); // Creates a new Card Object of the specific Card Number
							// and Reads the Parameters of This Card Number (if any)
							// then Sets this Card Object to GameObject Pointer of its Cell

	virtual ~PasteCardAction(); // A Virtual Destructor
};

