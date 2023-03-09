#pragma once

#include "Card.h"
#include"Ladder.h"
// [ CardTwo ] Summary:
// Its Apply() Function: Decrements the value of the passing player’s wallet by a value
// Its Parameters: The Wallet Value to decrease --> put it as a "data member" and read it in ReadCardParameters()

class CardTwo :	public Card
{
	// CardTwo Parameters:
	 Ladder* NextLadder; // the position to move the player to

public:
	CardTwo(const CellPosition & pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of CardTwo which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardTwo on the passed Player
	                        
                          // by decrementing the player's wallet by the walletAmount data member
	virtual void Copy(Card* source);
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& Infile);
	virtual ~CardTwo(); // A Virtual Destructor
};

