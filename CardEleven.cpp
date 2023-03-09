#include "CardEleven.h"

CardEleven::CardEleven(const CellPosition& pos) : Card(pos)  // set the cell position of the card
{
	cardNumber = 11; // set the inherited cardNumber data member with the card number (1 here)
	numberOfCards++;
}

CardEleven::~CardEleven(void)
{
}

void CardEleven::ReadCardParameters(Grid* pGrid)
{

	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	if (Price == -1) {
		do {
			pOut->PrintMessage("New CardEleven: Enter Price :");
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
int CardEleven::Price = -1;
int CardEleven::Fees = -1;
int CardEleven::owner = -1;
int CardEleven::numberOfCards = 0;
void CardEleven::setOwner(Player* player, Grid* pGrid) {
	owner = pGrid->getNumberByPlayer(player);
}
void CardEleven::deleteAction() {
	numberOfCards--;
	if (!numberOfCards) {
		owner = -1; Price = -1; Fees = -1;
	}
}
int CardEleven::getPrice() {
	return Price;
}

void CardEleven::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid,pPlayer);
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	bool accept = 0;
	if (owner == -1)
	{
		pOut->PrintMessage("Do You Want To Buy Station 11?,(1 for yes and 0 for no)");
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

void CardEleven::Save(ofstream& OutFile)
{
	OutFile << cardNumber << " ";
	Card::Save(OutFile);

	OutFile << " " << owner << " " << Price << " " << Fees << " " << numberOfCards << endl;
}
void CardEleven::Load(ifstream& Infile)
{
	Card::Load(Infile);
	Infile >> owner >> Price >> Fees >> numberOfCards;
}
void CardEleven::Copy(Card* source)
{

}