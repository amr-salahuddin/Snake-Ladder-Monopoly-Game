#include "AddSnakeAction.h"

#include "Input.h"
#include "Output.h"
#include "Snake.h"
//Added class
AddSnakeAction::AddSnakeAction(ApplicationManager* pApp) : Action(pApp)
{
	ok = true;
	// Initializes the pManager pointer of Action with the passed pointer
}

AddSnakeAction::~AddSnakeAction()
{
}

void AddSnakeAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Snake: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	//ADDED
	if (startPos.VCell() == 8) {
		pOut->PrintMessage("ERROR: Snake Start Can't Be On Last Row");
		ok = false;
		return;
	}
	if (startPos.GetCellNum() == 99)
	{
		pOut->PrintMessage("ERROR: Snake Start Can't Be On 99");
		pIn->GetCellClicked();
		pOut->ClearStatusBar();
		ok = false;
		return;
	}
	// /ADDED
	// Read the endPos parameter
	pOut->PrintMessage("New Snake: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();
	//ADDED
	if (startPos.HCell() != endPos.HCell())
	{
		pOut->PrintMessage("ERROR: Snake Start and End  Must Be On The Same Column");
		pOut->PrintMessage("ERROR: Snake End Can't Be Above Snake Start");
		ok = false;
		return;
	}
	else if (startPos.VCell() > endPos.VCell())
	{
		pOut->PrintMessage("ERROR: Snake End Can't Be Above Snake Start");
		pIn->GetCellClicked();
		ok=false;
		return;
	}
	if (endPos.GetCellNum() == 1)
	{
		pOut->PrintMessage("ERROR: Snake Start Can't Be On Last Row");
		ok = false;
		return;
	}
	// /ADDED



	///TODO: Make the needed validations on the read parameters
	

	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddSnakeAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	// Create a Snake object with the parameters read from the user
	if (ok) {
		Snake* pSnake = new Snake(startPos, endPos);

		Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

		// Add the card object to the GameObject of its Cell:
		bool added = pGrid->AddObjectToCell(pSnake);

		// if the GameObject cannot be added
		if (!added)
		{
			// Print an appropriate message
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
		}
	}
	// Here, the Snake is created and added to the GameObject of its Cell, so we finished executing the AddSnakeAction

}
