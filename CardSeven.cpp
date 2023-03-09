#include "CardSeven.h"

CardSeven::CardSeven(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 7; // set the inherited cardNumber data member with the card number (1 here)
}

CardSeven::~CardSeven(void)
{
}

void CardSeven::ReadCardParameters(Grid* pGrid)
{
	//No parameters to read for card 7
}

void CardSeven::Apply(Grid* pGrid, Player* pPlayer)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("You Have reached Card 7");
	pIn->GetCellClicked();

	pOut->PrintMessage("Resetting next Player");
	pIn->GetCellClicked();
	pOut->ClearStatusBar();
	pGrid->resetNextPlayers();
}
void CardSeven::Save(ofstream& OutFile)
{
	OutFile << cardNumber << " ";
	Card::Save(OutFile);
	OutFile << endl;
}
void CardSeven::Load(ifstream& Infile)
{
	Card::Load(Infile);
}
void CardSeven::Copy(Card* source)
{

}
