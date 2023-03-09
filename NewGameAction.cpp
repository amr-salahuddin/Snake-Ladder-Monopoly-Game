#include "NewGameAction.h"
#include"Grid.h"
#include"Output.h"
#include"Input.h"
#include"Player.h"
#include"CellPosition.h"
#include"CardEleven.h"
#include"CardNine.h"
#include"CardTen.h"
NewGameAction::NewGameAction(ApplicationManager* pApp) : Action(pApp)
{

}

void NewGameAction::ReadActionParameters()
{
	//No paramteres to read for this action
}

void NewGameAction::Execute()
{
	CellPosition start;
	start.SetHCell(0);
	start.SetVCell(8);
	Grid* pGrid= pManager->GetGrid();;
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pGrid->SetEndGame(false);
	//reseting players one by one
	for (int i = 0; i < 4; i++)
	{
		pGrid->setCurrentPlayerNumber(i);
		Player* pPlayer = pGrid->GetCurrentPlayer();
		pPlayer->SetWallet(100);
		pPlayer->SetTurnCount(0);
		pGrid->UpdatePlayerCell(pPlayer, start);
	}
	pGrid->setCurrentPlayerNumber(0);
	pOut->PrintMessage("You have clicked new game");
	pIn->GetCellClicked();
	CardTen::owner = -1;
	CardEleven::owner = -1;
	CardNine::owner = -1;

}
 NewGameAction::~NewGameAction()
 {

 }