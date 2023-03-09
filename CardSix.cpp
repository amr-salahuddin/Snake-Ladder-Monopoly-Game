#include "CardSix.h"

CardSix::CardSix(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 6; // set the inherited cardNumber data member with the card number (1 here)
}

CardSix::~CardSix(void)
{
}

void CardSix::ReadCardParameters(Grid* pGrid)
{


	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	do {
		pOut->PrintMessage("Please enter cell number");
		instCellNum = pIn->GetInteger(pOut);
		if (instCellNum < 1 || instCellNum>99||instCellNum==position.GetCellNum())
		{
			pOut->PrintMessage("Invalid Input!");
			pIn->GetCellClicked();
		}
	} while (instCellNum < 1 || instCellNum>99 || instCellNum == position.GetCellNum());
	pOut->ClearStatusBar();
}

void CardSix::Apply(Grid* pGrid, Player* pPlayer)
{

	//ReadCardParameters(pGrid);
	Card::Apply(pGrid,pPlayer);
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	CellPosition cp = CellPosition::GetCellPositionFromNum(instCellNum);
	pOut->PrintMessage("Moving to cell "+to_string(instCellNum));
	pIn->GetCellClicked();
	pOut->ClearStatusBar();
	pGrid->UpdatePlayerCell(pPlayer, cp);

}
void CardSix::Save(ofstream& OutFile)
{
	OutFile << cardNumber << " ";
	Card::Save(OutFile);
	OutFile << " "<<instCellNum << endl;
}
void CardSix::Load(ifstream& Infile)
{
	Card::Load(Infile);
	Infile >> instCellNum;
}
void CardSix::Copy(Card * source)
{
		instCellNum = dynamic_cast<CardSix*>(source)->instCellNum;
}
int CardSix::getinstnum()
{
	return instCellNum;
}