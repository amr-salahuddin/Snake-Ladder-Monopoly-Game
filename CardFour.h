#pragma once

#include "Card.h"

// [ CardFour ] Summary:
// Its Apply() Function: Decrements the value of the passing player’s wallet by a value
// Its Parameters: The Wallet Value to decrease --> put it as a "data member" and read it in ReadCardParameters()

class CardFour : public Card
{
	// CardFour Parameters:
	int walletAmount; // the wallet value to decrease from the player

public:
	CardFour(const CellPosition& pos); // A Constructor takes card position
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& Infile);
	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardFour which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardFour on the passed Player
													  // by decrementing the player's wallet by the walletAmount data member
	virtual void Copy(Card* source);
	virtual ~CardFour(); // A Virtual Destructor
};

