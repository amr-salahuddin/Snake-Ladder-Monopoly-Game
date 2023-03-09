#include "InputDiceValueAction.h"
#include "Input.h"
#include"Grid.h"
#include"Player.h"
InputDiceValueAction::InputDiceValueAction(ApplicationManager* pApp) :Action(pApp) {
}
void InputDiceValueAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	
		pOut->PrintMessage("Please, enter the dice value (any valid value from 1 to 6)");
		InputNumber = pIn->GetInteger(pOut);
}

void InputDiceValueAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	if (InputNumber <= 0 || InputNumber > 6)
	{
		pOut->PrintMessage("InvalidNumber!!, Click to continue");
		pIn->GetCellClicked();
		pOut->ClearStatusBar();
		return;
	}
	
	if (pGrid->GetEndGame())
	{
		return;
		// if game is over don't apply the dice
	}
	// -- If not ended, do the following --:

	
	pOut->PrintMessage("You entered: " + to_string(InputNumber) + " Please, click to continue");
	pIn->GetCellClicked();
	pOut->ClearStatusBar();
	// 3- Get the "current" player from pGrid
	Player* current = pGrid->GetCurrentPlayer();
	// 4- Move the currentPlayer using function Move of class player
	current->Move(pGrid,InputNumber);
	// 5- Advance the current player number of pGrid
	pGrid->AdvanceCurrentPlayer();
}

InputDiceValueAction::~InputDiceValueAction(){}