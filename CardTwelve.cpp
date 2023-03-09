#include "CardTwelve.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"

CardTwelve::CardTwelve(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 12; // set the inherited cardNumber data member with the card number (1 here)
}

CardTwelve::~CardTwelve(void)
{
}

void CardTwelve::ReadCardParameters(Grid* pGrid)
{

	//no parameters to read

}

void CardTwelve::Apply(Grid* pGrid, Player* pPlayer)
{


}
 void CardTwelve::Copy(Card* source)
{

}
  void CardTwelve::Save(ofstream& OutFile)
 {
	  OutFile << cardNumber << " ";
	  Card::Save(OutFile);
	  OutFile << endl;
 }
  void CardTwelve::Load(ifstream& Infile)
 {
	  Card::Load(Infile);

 }