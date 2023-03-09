#include "OpenGridAction.h"
#include"Grid.h"
#include"Player.h"
#include<fstream>
#include"CardEleven.h"
#include"CardNine.h"
#include"CardTen.h"
OpenGridAction::OpenGridAction(ApplicationManager* pApp) : Action(pApp)
{

}

void OpenGridAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Please, Enter FileName");
	FileName = pIn->GetSrting(pOut);
	FileName += ".txt";
}

void OpenGridAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	CellPosition start;
	start.SetHCell(0);
	start.SetVCell(8);
	ifstream InputFile(FileName);
	if (!InputFile.is_open())
	{
		pOut->PrintMessage("Can't Open Specified File");
		pIn->GetCellClicked();
		pOut->ClearStatusBar();
		return;
	}
	pGrid->ClearAll();
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
	pOut->PrintMessage("Loading File, Click to continue");
	pIn->GetCellClicked();
	pOut->ClearStatusBar();
	pGrid->LoadAll(InputFile);
	InputFile.close();

}


OpenGridAction::~OpenGridAction()
{

}