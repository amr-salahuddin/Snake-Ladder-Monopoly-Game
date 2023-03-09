#include "DeleteObjectAction.h"
#include "Input.h"
#include "Output.h"
#include"Grid.h"
#include"GameObject.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
DeleteObjectAction::DeleteObjectAction(ApplicationManager* pApp):Action(pApp) {
}

void DeleteObjectAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Please select cell to delete from (start of a ladder, end of a snake or a card)");
	destination = pIn->GetCellClicked();
}

void DeleteObjectAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	if (dynamic_cast<CardNine*>(pGrid->getCard(destination)))
	{
		CardNine::deleteAction();
	}
	else if (dynamic_cast<CardTen*>(pGrid->getCard(destination)))
	{
		CardTen::deleteAction();
	}
	else if (dynamic_cast<CardEleven*>(pGrid->getCard(destination)))
	{
		CardEleven::deleteAction();
	}
	GameObject* removed=pGrid->RemoveObjectFromCell(destination);
	if (removed == NULL)
		pOut->PrintMessage("Error can't remove object from the chosen cell");
	else
	{
	
		delete removed;
		pOut->PrintMessage("Successfully removed Object");
		pIn->GetCellClicked();
		pOut->ClearStatusBar();
		
	}
	//Cards91011
	
	// /Cards91011
 }

 DeleteObjectAction::~DeleteObjectAction()
 {
	
 }