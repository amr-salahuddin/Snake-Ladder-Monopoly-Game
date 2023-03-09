#include "CardNine.h"

CardNine::CardNine(const CellPosition& pos) : Card(pos)  // set the cell position of the card
{
	cardNumber = 9; // set the inherited cardNumber data member with the card number (1 here)
	numberOfCards++;
}

CardNine::~CardNine(void)
{
}

void CardNine::ReadCardParameters(Grid* pGrid)
{

	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	if (Price == -1) {
		do {
			pOut->PrintMessage("New CardNine: Enter Price :");
			Price = pIn->GetInteger(pOut);
			if (Price <= 0)
			{
				pOut->PrintMessage("Invalid Input!");
				pIn->GetCellClicked();
			}
		} while (Price <= 0);
		do {
			pOut->PrintMessage("Enter Fees:");
			Fees = pIn->GetInteger(pOut);
			if (Fees <= 0)
			{
				pOut->PrintMessage("Invalid Input!");
				pIn->GetCellClicked();
			}
		} while (Fees <= 0);
		pOut->ClearStatusBar();
	}

}
int CardNine::Price = -1;
int CardNine::Fees = -1;
int CardNine::owner = -1;
int CardNine::numberOfCards = 0;
void CardNine::setOwner(Player* player, Grid* pGrid) {
	owner = pGrid->getNumberByPlayer(player);
}
void CardNine::deleteAction() {
	numberOfCards--;
	if (!numberOfCards) {
		owner = -1; Price = -1; Fees = -1;
	}
}
int CardNine::getPrice() {
	return Price;
}

void CardNine::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	bool accept = 0;
	if (owner == -1)
	{
		pOut->PrintMessage("Do You Want To Buy Station 9?,(1 for yes and 0 for no)");
		accept = pIn->GetInteger(pOut);
		pOut->ClearStatusBar();
		if (accept && pPlayer->GetWallet() >= Price)
		{
			pPlayer->SetWallet(pPlayer->GetWallet() - Price);
			owner = pGrid->getNumberByPlayer(pPlayer);
		}
		else if (pPlayer->GetWallet() < Price)
		{
			pOut->PrintMessage("Sorry, you don't have enough money");
			pIn->GetCellClicked();
			pOut->ClearStatusBar();

		}
	}
	else if (pGrid->getPlayerByNumber(owner) != pPlayer) {
		pOut->PrintMessage("Paying fees");
		pIn->GetCellClicked();
		pOut->ClearStatusBar();
		pPlayer->SetWallet(pPlayer->GetWallet() - Fees);
		pGrid->getPlayerByNumber(owner)->SetWallet(pGrid->getPlayerByNumber(owner)->GetWallet() + Fees);
	}

	

}

void CardNine::Save(ofstream& OutFile)
{
	OutFile << cardNumber << " ";
	Card::Save(OutFile);

	OutFile << " " << owner << " " << Price << " " << Fees << " " << numberOfCards << endl;
}
void CardNine::Load(ifstream& Infile)
{
	Card::Load(Infile);
	Infile >> owner >> Price >> Fees >> numberOfCards;
}
void CardNine::Copy(Card* source)
{

}