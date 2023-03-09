#pragma once

#include "Card.h"


class CardThree :	public Card
{

public:
	CardThree(const CellPosition & pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of CardThree which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardThree on the passed Player
	                                                  // by decrementing the player's wallet by the walletAmount data member
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& Infile);
	virtual void Copy(Card* source);
	virtual ~CardThree(); // A Virtual Destructor
};

