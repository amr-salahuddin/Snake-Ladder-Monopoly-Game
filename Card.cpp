#include "Card.h"
#include"Ladder.h"
#include"Snake.h"
#include"CardOne.h"
#include"CardTwo.h"
#include"CardThree.h"
#include"CardFour.h"
#include"CardFive.h"
#include"CardSix.h"
#include"CardSeven.h"
#include"CardEight.h"
#include"CardNine.h"
#include"CardTen.h"
#include"CardEleven.h"
#include"CardTwelve.h"
Card::Card(const CellPosition& pos) : GameObject(pos) // sets the cell position of the GameObject
{
}

void Card::SetCardNumber(int cnum)
{
	cardNumber = cnum; // needs validation
}

int Card::GetCardNumber()
{
	return cardNumber;
}

void Card::Draw(Output* pOut) const
{

	///TODO: call the appropriate Ouput function that draws a cell containing the "cardNumber" in "position"
	pOut->DrawCell(position, cardNumber);
}

void Card::ReadCardParameters(Grid* pGrid)
{
	// we should not make it pure virtual because some Cards doesn't have parameters
	// and if we make it pure virtual, that will make those Cards abstract classes
}

void Card::Apply(Grid* pGrid, Player* pPlayer)
{
	// As written below the "Roll Dice" action in the document ==> Check the Project Document
	// "If a player reaches a card of any other type", the following message should be printed then wait mouse click

	pGrid->PrintErrorMessage("You have reached card " + to_string(cardNumber) + ". Click to continue ...");
}
void Card::ChangePosition(CellPosition pos)
{
	position = pos;
}
//Added
bool Card::getCopy()
{
	return copy;
}
bool Card::IsOverlapping(GameObject* newobj) 
{ 
	return false;
}

void Card::setCopy(bool setter) { copy = setter; }
void Card::Save(ofstream& OutFile)
{
	OutFile << position.GetCellNum();
}
void Card::Load(ifstream& Infile)
{
	int pos;
	CellPosition cp;
	Infile >> pos;
	position = cp.GetCellPositionFromNum(pos);
}
Card::~Card()
{
}
