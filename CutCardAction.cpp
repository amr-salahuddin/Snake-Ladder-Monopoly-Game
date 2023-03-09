#include "CutCardAction.h"
#include "Input.h"
#include "Output.h"
#include"Grid.h"
#include"Card.h"
//Added class
CutCardAction::CutCardAction(ApplicationManager* pApp) : Action(pApp)
{

}

void CutCardAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("click on the source cell");
	CardCell = pIn->GetCellClicked();
}

void CutCardAction::Execute() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	ReadActionParameters();
	if (CardCell.IsValidCell()) {
		
		if (pGrid->getCard(CardCell))
		{
			if (pGrid->GetClipboard() != NULL) {
				if (!pGrid->GetClipboard()->getCopy())
				{
					pGrid->AddObjectToCell(pGrid->GetClipboard());
				}
				else
					delete pGrid->GetClipboard();
			}
			pOut->PrintMessage("Successfully cutted the card, Click to continue");
			pGrid->SetClipboard(pGrid->getCard(CardCell));
			pGrid->RemoveObjectFromCell(CardCell);
			pGrid->GetClipboard()->setCopy(false);
		}
		else
		{
			pOut->PrintMessage("Action failed, Click to continue");
			pGrid->SetClipboard(NULL);
		}
		pIn->GetCellClicked();
		pOut->ClearStatusBar();
	}
	else
	{
		pOut->PrintMessage("Action failed, Click to continue");
		pIn->GetCellClicked();
		pOut->ClearStatusBar();
		CardCell = NULL;
	}
}

CutCardAction:: ~CutCardAction()
{

}

