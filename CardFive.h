#pragma once

#include "Card.h"

// [ CardFive ] Summary:
// Its Apply() Function: Decrements the value of the passing player’s wallet by a value
// Its Parameters: The Wallet Value to decrease --> put it as a "data member" and read it in ReadCardParameters()

class CardFive :	public Card
{
	// CardFive Parameters:
	int walletAmount; // the wallet value to decrease from the player

public:
	CardFive(const CellPosition & pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of CardFive which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardFive on the passed Player
	                                                  // by decrementing the player's wallet by the walletAmount data member
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& Infile);
	virtual void Copy(Card* source);
	virtual ~CardFive(); // A Virtual Destructor
};

