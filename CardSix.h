#pragma once

#include "Card.h"


class CardSix :	public Card
{
	int instCellNum; 

public:
	CardSix(const CellPosition & pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of CardSix which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardSix on the passed Player
	                                                  // by decrementing the player's wallet by the walletAmount data member
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& Infile);
	virtual void Copy(Card* source);
	int getinstnum();
	virtual ~CardSix(); // A Virtual Destructor
};

