#include "CardEight.h"

CardEight::CardEight(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 8; // set the inherited cardNumber data member with the card number (1 here)
}

CardEight::~CardEight(void)
{
}

void CardEight::ReadCardParameters(Grid * pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Please, enter wallet amount");
	walletAmount=pIn->GetInteger(pOut);
	
}

void CardEight::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	int choice;
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	do {
		pOut->PrintMessage("Press 1 to go to prison or 2 to pay the fees");
		choice = pIn->GetInteger(pOut);
		if (choice != 1 && choice != 2)
			pOut->PrintMessage("Invalid Choice");
		pIn->GetCellClicked();
		pOut->ClearStatusBar();
	} while (choice != 1 && choice != 2);
	if (choice == 1)
	{
		pOut->PrintMessage("You are in prison for three turns, Click to continue");
		pIn->GetCellClicked();
		pOut->ClearStatusBar();
		pPlayer->setInPrison(true);
		pPlayer->setStoppedturns(3);
	}
	else
	{
		if (pPlayer->GetWallet() >= walletAmount)
			pPlayer->SetWallet(pPlayer->GetWallet() - walletAmount);
		else {
			pOut->PrintMessage("There is no enough amount of money, you are in prison");
			pPlayer->setStoppedturns(3);
			pIn->GetCellClicked();
			pOut->ClearStatusBar();
			pPlayer->setInPrison(true);
		}
	}
}
void CardEight::Save(ofstream& OutFile)
{
	OutFile << cardNumber << " ";
	Card::Save(OutFile);
	OutFile << " " << walletAmount << endl;
}
void CardEight::Load(ifstream& Infile)
{
	Card::Load(Infile);
	Infile >> walletAmount;
}
void CardEight::Copy(Card* source)
{
	walletAmount = dynamic_cast<CardEight*>(source)->walletAmount;
}