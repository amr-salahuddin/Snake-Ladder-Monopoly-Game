#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"

AddLadderAction::AddLadderAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	ok = true;
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();
	//ADDED
	if (startPos.GetCellNum() == 1)
	{
		pOut->PrintMessage("ERROR: Ladder Start Can't Be On First Cell");
		ok = false;
		return;
	}
	else if (startPos.VCell() == 0) {
		pOut->PrintMessage("ERROR: Ladder Start Can't Be On First Row");
		ok = false;
		return;
	}
	
	// /ADDED
	// Read the endPos parameter
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();
	if (endPos.GetCellNum() == 99)
	{
		pOut->PrintMessage("ERROR: Ladder End Can't Be 99");
		ok = false;
		return;
	}
	//ADDED
	if (startPos.HCell() != endPos.HCell())
	{
		pOut->PrintMessage("ERROR: Ladder Start and End  Must Be On The Same Column");
		startPos.SetVCell(-1);
		return;
	}
	if (startPos.VCell() < endPos.VCell())
	{
		pOut->PrintMessage("ERROR: Ladder End Can't Be Above Ladder Start");
		startPos.SetVCell(-1);
		return;
	}
	// /ADDED

	///TODO: Make the needed validations on the read parameters



	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddLadderAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	// Create a Ladder object with the parameters read from the user
	if (startPos.VCell() != -1&&ok)
	{		Ladder* pLadder = new Ladder(startPos, endPos);

	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pLadder);

	// if the GameObject cannot be added
	if (!added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction
}
}
