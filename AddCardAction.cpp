#include "AddCardAction.h"

#include "Input.h"
#include "Output.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"

AddCardAction::AddCardAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddCardAction::~AddCardAction()
{
}

void AddCardAction::ReadActionParameters()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	Input* pIn = pManager->GetGrid()->GetInput();
	Output* pOut = pManager->GetGrid()->GetOutput();
	pOut->PrintMessage("New Card: Enter Card number ");
	int num;
	num = pIn->GetInteger(pOut);
	if (num < 1 || num>12)
	{		pOut->PrintMessage("There is no such Card number !!, Please try again");
	pIn->GetCellClicked();
	pOut->ClearStatusBar();
	return;
}
	cardNumber = num;
	pOut->PrintMessage("New Card: Click on its Position ...");
	cardPosition = pIn->GetCellClicked();
	if (cardPosition.GetCellNum() == 99 || cardPosition.GetCellNum() == 1)
	{
		pOut->PrintMessage("Invalid Position !");
		pIn->GetCellClicked();
		pOut->ClearStatusBar();
		cardPosition.SetVCell(-1);
	}
	pOut->ClearStatusBar();
	// == Here are some guideline steps (numbered below) to implement this function ==
	// 1- Get a Pointer to the Input / Output Interfaces

	// 2- Read the "cardNumber" parameter and set its data member

	// 3- Read the "cardPosition" parameter (its cell position) and set its data member

	// 4- Make the needed validations on the read parameters

	// 5- Clear status bar
}

void AddCardAction::Execute()
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	ReadActionParameters();
	if (cardPosition.VCell() == -1)
		return;
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- The first line of any Action Execution is to read its parameter first

	// 2- Switch case on cardNumber data member and create the appropriate card object type
	Card* pCard = NULL; // will point to the card object type
	switch (cardNumber)
	{
	case 1:
		pCard = new CardOne(cardPosition);
		break;
	case 2:
		pCard = new CardTwo(cardPosition);
		break;
	case 3:
		pCard = new CardThree(cardPosition);
		break;
	case 4:
		pCard = new CardFour(cardPosition);
		break;
	case 5:
		pCard = new CardFive(cardPosition);
		break;
	case 6:
		pCard = new CardSix(cardPosition);
		break;
	case 7:
		pCard = new CardSeven(cardPosition);
		break;
	case 8:
		pCard = new CardEight(cardPosition);
		break;
	case 9:
		pCard = new CardNine(cardPosition);
		break;
	case 10:
		pCard = new CardTen(cardPosition);
		break;
	case 11:
		pCard = new CardEleven(cardPosition);
		break;
	case 12:
		pCard = new CardTwelve(cardPosition);
		break;
		// A- Add the remaining cases

	}

	// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL)
	if (pCard)
	{

		// A- We get a pointer to the Grid from the ApplicationManager
		Grid* pGrid = pManager->GetGrid();
		// B- Make the "pCard" reads its card parameters: ReadCardParameters(), It is virtual and depends on the card type
		pCard->ReadCardParameters(pGrid);
		// C- Add the card object to the GameObject of its Cell:
		bool check = pGrid->AddObjectToCell(pCard);
		// D- if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar
		if (!check)
			pManager->GetGrid()->PrintErrorMessage("Error: Can't add card ");
	}

	// Here, the card is created and added to the GameObject of its Cell, so we finished executing the AddCardAction

}
