#include "CardTwo.h"

CardTwo::CardTwo(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 2; // set the inherited cardNumber data member with the card number (1 here)
}

CardTwo::~CardTwo(void)
{
}

void CardTwo::ReadCardParameters(Grid * pGrid)
{
	
	
   //There are no parameters to read in card two
	
	// 1- Get a Pointer to the Grid
	// 2-Get cell position of the next ladder
	// 3- Clear the status bar

}

void CardTwo::Apply(Grid* pGrid, Player* pPlayer)
{
		//Getting position of the next ladder
	Card::Apply(pGrid, pPlayer);
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("CardTwo: Shifting to the next ladder, Please,click to proceed");
	pIn->GetCellClicked();
		pOut->ClearStatusBar();
	NextLadder = pGrid->GetNextLadder(GetPosition());
	// Call Apply() of the base class Card to print the message that you reached this card number
	//Move player to the start of the next ladder
	if(NextLadder != NULL)
	pGrid->UpdatePlayerCell(pPlayer,NextLadder->GetPosition());
	else
	{
		
		pOut->PrintMessage("There are no next ladders, Sorry");
		pIn->GetCellClicked();
		pOut->ClearStatusBar();

	}
}
void CardTwo::Save(ofstream& OutFile)
{
	OutFile << cardNumber<<" ";
	Card::Save(OutFile);
	OutFile<< endl;
}
void CardTwo::Load(ifstream& Infile)
{
	Card::Load(Infile);
}
 void CardTwo::Copy(Card* source)
{

}