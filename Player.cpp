#include "Player.h"
#include "GameObject.h"
#include"CardTwo.h"
#include"CardSix.h"
Player::Player(Cell* pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum),card4count(0)
{
	this->pCell = pCell;
	this->turnCount = 0;
	InPrison = false;
	stoppedturns = 0;
	card4 = false;
	card3 = false;
	card5 = false;
	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======
void Player::setStoppedturns(int a)
{
	stoppedturns = a;
}
int Player::getStoppedturns()
{
	return stoppedturns;
}
void Player::setCard4(bool prmCard4)
{
	card4 = prmCard4;
}
void Player::SetCell(Cell* cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}
void Player::setInPrison(bool a)
{
	InPrison = a;
}
bool Player::getInPrison()
{
	return InPrison;
}
void Player::SetWallet(int wallet)
{
	//ADDED
	//if (wallet < 0)
	//	wallet = 0;
	// /ADDED
	this->wallet = wallet;
	// Make any needed validations
}

int Player::GetWallet() const
{
	return wallet;
}

int Player::GetTurnCount() const
{
	return turnCount;
}
void  Player::SetTurnCount(int a)
{
	if (a >= 0 && a <= 2)
		turnCount = a;
}

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];


	///TODO: use the appropriate output function to draw the player with "playerColor"
	//ADDED
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor);
	// /ADDED
}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;


	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)
	//ADDED
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);
	// /ADDED
}

// ====== Game Functions ======

void Player::Move(Grid* pGrid, int diceNumber)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	//ADDED
	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
	
	if (card4count == 1)
		card4 = 0;
	if (card4)
	{
		pGrid->GetOutput()->PrintMessage("Dice roll is cancelled, click to continue");
		pGrid->GetInput()->GetCellClicked();
		pGrid->GetOutput()->ClearStatusBar();
			card4count++;
	}
	if (stoppedturns > 0)
		stoppedturns--;
	else
		setInPrison(false);
	if (!getInPrison())
		turnCount++;
	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)

	if (turnCount == 3 && !getInPrison()) {
		wallet += diceNumber;
		turnCount = 0;
		return;
	}
	 if (card5)
	{
		CellPosition cp;
		if (GetCell()->GetCellPosition().GetCellNum() >= 4)
		{
			cp = pCell->GetCellPosition();
			stepCount -= diceNumber;
			justRolledDiceNum = diceNumber;
			cp.AddCellNum(-justRolledDiceNum);
		}
		else
		{

			cp.SetHCell(0);
			cp.SetVCell(8);
		}
		pGrid->UpdatePlayerCell(this, cp);
	 if (pCell->GetGameObject() != NULL)
		pCell->GetGameObject()->Apply(pGrid, this);
	 card5 = 0;
	}
	else if (!card4 && !getInPrison()) {

		stepCount += diceNumber;
		// 3- Set the justRolledDiceNum with the passed diceNumber
		justRolledDiceNum = diceNumber;
		// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
		//    Using the appropriate function of CellPosition class to update "pos"
		
		CellPosition cp = pCell->GetCellPosition();
		cp.AddCellNum(justRolledDiceNum);
		// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
		//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position
		pGrid->UpdatePlayerCell(this, cp);
		// 6- Apply() the game object of the reached cell (if any)
		CellPosition prevpos(231);
		while (pCell->GetGameObject()!=NULL&&(pCell->GetCellPosition().GetCellNum()!=prevpos.GetCellNum())) {
			prevpos = pCell->GetCellPosition();
			
				pCell->GetGameObject()->Apply(pGrid, this);
		}
		// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
		if (pCell->GetCellPosition().GetCellNum() + justRolledDiceNum > 99 && wallet>=0)
		{
			cp.SetVCell(0);
			cp.SetHCell(10);
			pGrid->UpdatePlayerCell(this, cp);
			pGrid->SetEndGame(true);
			pGrid->GetOutput()->PrintMessage("Player number " + to_string(pGrid->getCurrentPlayerNumber()) + " Wins Game Over!");
		}
		// /ADDED
	}
	
}

void Player::setCard3(bool crd3prm)
{
	card3 = crd3prm;
}
void Player::AppendPlayerInfo(string& playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(";
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}
bool Player::getCard3()
{
	return card3;
}
void Player::setCard5(bool crd5prm)
{
	card5 = crd5prm;
}
