#include "CardFive.h"

CardFive::CardFive(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 5; // set the inherited cardNumber data member with the card number (1 here)
}

CardFive::~CardFive(void)
{
}

void CardFive::ReadCardParameters(Grid * pGrid)
{
	
	//No parameters to read 

}

void CardFive::Apply(Grid* pGrid, Player* pPlayer)
{
		
	Card::Apply(pGrid, pPlayer);
	pGrid->GetOutput()->PrintMessage("returning just rolled dice steps");
	pGrid->GetInput()->GetCellClicked();
	pGrid->GetOutput()->ClearStatusBar();
	pPlayer->setCard5(1);

}
void CardFive::Save(ofstream& OutFile)
{
	OutFile << cardNumber << " ";
	Card::Save(OutFile);
	OutFile << endl;
 }
void CardFive::Load(ifstream& Infile)
{
	Card::Load(Infile);

 }
void CardFive::Copy(Card* source)
{

 }