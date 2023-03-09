#include "PlayToDesign.h"
#include "Input.h"
#include "Output.h"
#include"Grid.h"
#include "Player.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
PlayToDesign::PlayToDesign(ApplicationManager* pApp) :Action(pApp) {


}
void PlayToDesign::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
}

void PlayToDesign::Execute() {
	CellPosition start;
	start.SetHCell(0);
	start.SetVCell(8);
	Grid* pGrid = pManager->GetGrid();;
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->CreateDesignModeToolBar();
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
	CardTen::owner = -1;
	CardEleven::owner = -1;
	CardNine::owner = -1;


}