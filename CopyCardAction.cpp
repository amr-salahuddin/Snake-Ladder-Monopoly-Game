#include "CopyCardAction.h"
#include "Input.h"
#include "Output.h"
#include"Grid.h"
#include"Card.h"
//Added class
CopyCardAction::CopyCardAction(ApplicationManager* pApp) : Action(pApp)
{

}

void CopyCardAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("click on the source cell");
	CardCell = pIn->GetCellClicked();
}

void CopyCardAction::Execute() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	ReadActionParameters();
	if (CardCell.IsValidCell())
	{
		if (pGrid->GetClipboard() != NULL) {
			if (!pGrid->GetClipboard()->getCopy())
			{
				pGrid->AddObjectToCell(pGrid->GetClipboard());
			}
		}
		if (pGrid->getCard(CardCell))
		{

			pOut->PrintMessage("Successfully copied the card, Click to continue");
			pGrid->SetClipboard(pGrid->getCard(CardCell));
			pGrid->GetClipboard()->setCopy(true);
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

CopyCardAction:: ~CopyCardAction()
{

}

