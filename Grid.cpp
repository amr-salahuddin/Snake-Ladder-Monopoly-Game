#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include"Snake.h"
#include "Card.h"
#include "Player.h"
#include<iostream>
#include<fstream>
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
using namespace std;
Grid::Grid(Input* pIn, Output* pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells - 1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject* pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject* pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if (pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false
		if (Isoverlapping(pNewObject))
		{
			return false;

		}
		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		cout << pos.GetCellNumFromPosition(pos);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}

bool Grid::Isoverlapping(GameObject* newobj)//Added
{
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if(CellList[i][j]->GetGameObject()!=NULL)
				if (CellList[i][j]->GetGameObject()->IsOverlapping(newobj))
					return true;
		}
	}
	return false;
}
// Note: You may need to change the return type of this function (Think)
GameObject* Grid::RemoveObjectFromCell(const CellPosition& pos)
{
	GameObject* removed = NULL;
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed
		removed = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if (removed != NULL)
			CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
	}
	return removed;
}

void Grid::UpdatePlayerCell(Player* player, const CellPosition& newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell* newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}
Player* Grid::getPlayerByNumber(int n) {
	return PlayerList[n];
}
int Grid::getNumberByPlayer(Player* player) {
	for (size_t i = 0; i <= 3; i++)
	{
		if (PlayerList[i] == player)
			return i;
	}
}
void Grid::resetNextPlayers()
{
	int CurrentPos;
	Player* current;
	CellPosition start;
	start.SetHCell(0);
	start.SetVCell(8);
	current = GetCurrentPlayer();
	CurrentPos = current->GetCell()->GetCellPosition().GetCellNum();
	/*for (int i = 0; (i <= 3); i++)
	{
		if (i != currPlayerNumber && PlayerList[i]->GetCell()->GetCellPosition().GetCellNum() > CurrentPos) {

			temp[j++] = PlayerList[i];
		}
	}*/
	for (size_t i = 1 + CurrentPos; i <= 99; i++)
	{
		bool flag = 0;
		for (size_t j = 0; j < 4; j++)
		{
			if (PlayerList[j]->GetCell()->GetCellPosition().GetCellNum() == i) {
				UpdatePlayerCell(PlayerList[j], start);
				flag = 1;
			}
		}
		if (flag)
			break;
	}

}

// ========= Setters and Getters Functions =========


Input* Grid::GetInput() const
{
	return pIn;
}

Output* Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card* pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card* Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}
void Grid::setCurrentPlayerNumber(int a)
{
	currPlayerNumber = a;
}

void Grid::AdvanceCurrentPlayer()
{
	if (!GetCurrentPlayer()->getCard3())
		currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
	else {
		pOut->PrintMessage("Extra Dice Roll");
		GetCurrentPlayer()->setCard3(0);
		pIn->GetCellClicked();
		pOut->ClearStatusBar();
	}
}

// ========= Other Getters =========
int Grid::getCurrentPlayerNumber()
{
	return currPlayerNumber;
}

Card* Grid::getCard(const CellPosition& position)
{
	int H = position.HCell();
	int V = position.VCell();
	cout << position.GetCellNumFromPosition(position);
	if (CellList[V][H]->HasCard())
	{
		return dynamic_cast<Card*>(CellList[position.VCell()][position.HCell()]->GetGameObject());
	}
}
Player* Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Ladder* Grid::GetNextLadder(const CellPosition& position)
{

	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			//TODO: Check if CellList[i][j] has a ladder, if yes return it
			if (CellList[i][j]->HasLadder())
				return dynamic_cast<Ladder*>(CellList[i][j]->GetGameObject());
		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}


// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount - 1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}

void Grid::SaveAll(ofstream& OutputFile)
{
	OutputFile << "SLGROSOMARAMRSECTION1DECRYPTIONOFFILE" << endl;
	int nLaddders = 0, nSnakes = 0, nCards = 0;
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->HasLadder())
			{
				nLaddders++;
			}
			else if (CellList[i][j]->HasSnake())
				nSnakes++;
			else if (CellList[i][j]->HasCard())
				nCards++;
		}
	}
	OutputFile << nLaddders << endl;
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->HasLadder())
			{
				CellList[i][j]->GetGameObject()->Save(OutputFile);
			 }
		}
	}
	OutputFile << nSnakes << endl;
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->HasSnake())
			{
				CellList[i][j]->GetGameObject()->Save(OutputFile);
			}
		}
	}
	OutputFile << nCards << endl;
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->HasCard())
			{
				CellList[i][j]->GetGameObject()->Save(OutputFile);
			}
		}
	}
}
void Grid::LoadAll(ifstream &InputFile)
{
	string code, n;
	int cardnum;
	GameObject* newobj=NULL;
	CellPosition def;
	def.SetHCell(0);
	def.SetVCell(8);
	
		getline(InputFile, code);
		if (code != "SLGROSOMARAMRSECTION1DECRYPTIONOFFILE")
		{
			pOut->PrintMessage("Invalid, File!!");
			pIn->GetCellClicked();
			pOut->ClearStatusBar();
			return;
		}
		InputFile >> n;
		for (int i = 1; i <= stoi(n); i++)
		{
			newobj= new Ladder(def,def);
			newobj->Load(InputFile);
			AddObjectToCell(newobj);
		}
		InputFile>>n;
		for (int i = 1; i <= stoi(n); i++)
		{
			newobj = new Snake(def,def);
			newobj->Load(InputFile);
			AddObjectToCell(newobj);
		}
		InputFile >> n;
		for (int i = 1; i <= stoi(n); i++)
		{
			InputFile >> cardnum;
			switch (cardnum)
			{
			case 1:
				newobj = new CardOne(def);
				break;
			case 2:
				newobj = new CardTwo(def);
				break;
			case 3:
				newobj = new CardThree(def);
				break;
			case 4:
				newobj = new CardFour(def);
				break;
			case 5:
				newobj = new CardFive(def);
				break;
			case 6:
				newobj = new CardSix(def);
				break;
			case 7:
				newobj = new CardSeven(def);
				break;
			case 8:
				newobj = new CardEight(def);
				break;
			case 9:
				newobj = new CardNine(def);
				break;
			case 10:
				newobj = new CardTen(def);
				break;
			case 11:
				newobj = new CardEleven(def);
				break;
			case 12:
				newobj = new CardTwelve(def);
				break;
			}
			newobj->Load(InputFile);
			AddObjectToCell(newobj);
		}
		
	}

void Grid::ClearAll()
{
	GameObject* removed;
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			removed = CellList[i][j]->GetGameObject();
			if (removed != NULL) {
				delete removed;
				removed = RemoveObjectFromCell(CellList[i][j]->GetCellPosition());
			}
		}
	}
}
Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		delete PlayerList[i];
	}
}