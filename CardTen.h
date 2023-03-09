#pragma once

#include "Card.h"

// [ CardTen ] Summary:
// Its Apply() Function: Decrements the value of the passing player’s wallet by a value
// Its Parameters: The Wallet Value to decrease --> put it as a "data member" and read it in ReadCardParameters()

class CardTen : public Card
{
	// CardTen Parameters:
	static	int Price; // the wallet value to decrease from the player
	static int Fees; // the wallet value to decrease from the player
	static int numberOfCards;
public:
	static int owner;
	CardTen(const CellPosition& pos); // A Constructor takes card position
	static int getPrice();
	static void deleteAction();
	static void setOwner(Player*, Grid*);
	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardTen which is: walletAmount
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& Infile);
	virtual void Copy(Card*source);
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardTen on the passed Player
													  // by decrementing the player's wallet by the walletAmount data member

	virtual ~CardTen(); // A Virtual Destructor
};

