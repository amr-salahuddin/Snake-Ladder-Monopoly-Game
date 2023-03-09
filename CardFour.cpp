#include "CardFour.h"

CardFour::CardFour(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 4; // set the inherited cardNumber data member with the card number (1 here)
}

CardFour::~CardFour(void)
{
}

void CardFour::ReadCardParameters(Grid* pGrid)
{
//No parameters to read
}

void CardFour::Apply(Grid* pGrid, Player* pPlayer)
{

	Card::Apply(pGrid, pPlayer);
	pPlayer->setCard4(true);

}
void CardFour::Save(ofstream& OutFile)
{
	OutFile << cardNumber << " ";
	Card::Save(OutFile);
	OutFile << endl;
}
void CardFour::Load(ifstream& Infile)
{
	Card::Load(Infile);
}
void CardFour::Copy(Card* Source)
{

}