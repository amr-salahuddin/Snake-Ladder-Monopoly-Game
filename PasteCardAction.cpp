#include "PasteCardAction.h"
#include "Input.h"
#include "Output.h"
#include"Grid.h"
#include"Card.h"
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
PasteCardAction::PasteCardAction(ApplicationManager* pApp) : Action(pApp)
{

}

void PasteCardAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("click on the destination cell");
	CardCell = pIn->GetCellClicked();
}

void PasteCardAction::Execute() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	ReadActionParameters();
	if (pGrid->GetClipboard() == NULL)
	{
		pOut->PrintMessage("No cards to paste");
		pIn->GetCellClicked();
		pOut->ClearStatusBar();
		return;
	}
	if (CardCell.IsValidCell()) {
		if (!pGrid->getCard(CardCell))
		{
			Card* card;
			pOut->PrintMessage("Successfully pasted the card, Click to continue");
			Card* tmp = pGrid->GetClipboard();
			if (pGrid->GetClipboard()->getCopy())
			{
				if (dynamic_cast<CardOne*>(tmp)) {
					card = new CardOne(CardCell);
				}
				else if (dynamic_cast<CardTwo*>(tmp)) {
					card = new CardTwo(CardCell);
				}
				else if (dynamic_cast<CardThree*>(tmp)) {
					card = new CardThree(CardCell);
				}
				else if (dynamic_cast<CardFour*>(tmp)) {
					card = new CardFour(CardCell);
				}
				else if (dynamic_cast<CardFive*>(tmp)) {
					card = new CardFive(CardCell);
				}
				else if (dynamic_cast<CardSix*>(tmp)) {
					card = new CardSix(CardCell);
				}
				else if (dynamic_cast<CardSeven*>(tmp)) {
					card = new CardSeven(CardCell);
				}
				else if (dynamic_cast<CardEight*>(tmp)) {
					card = new CardEight(CardCell);
				}
				else if (dynamic_cast<CardNine*>(tmp)) {
					card = new CardNine(CardCell);
				}
				else if (dynamic_cast<CardTen*>(tmp)) {
					card = new CardTen(CardCell);
				}
				else if (dynamic_cast<CardEleven*>(tmp)) {
					card = new CardEleven(CardCell);
				}
				else if (dynamic_cast<CardTwelve*>(tmp)) {
					card = new CardTwelve(CardCell);
				}
				card->Copy(tmp);
				if(dynamic_cast<CardSix*>(card))
				if (dynamic_cast<CardSix*>(card)->getinstnum() == CardCell.GetCellNum())
				{
					pOut->PrintMessage("Can't Paste Card Here");
					pIn->GetCellClicked();
					pOut->ClearStatusBar();
					return;
				}
			}
			else
			{ 
				card = pGrid->GetClipboard();
				if (dynamic_cast<CardSix*>(card))
				if (dynamic_cast<CardSix*>(card)->getinstnum() == CardCell.GetCellNum())
				{
					pOut->PrintMessage("Can't Paste Card Here");
					pIn->GetCellClicked();
					pOut->ClearStatusBar();
					return;
				}
			}
			card->ChangePosition(CardCell);
			bool check = pGrid->AddObjectToCell(card);
			// D- if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar
			if (!check)
				pManager->GetGrid()->PrintErrorMessage("Error: Can't add card ");
			pGrid->SetClipboard(NULL);
		}
		else
			pOut->PrintMessage("Action failed, Click to continue");
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

PasteCardAction:: ~PasteCardAction()
{

}

