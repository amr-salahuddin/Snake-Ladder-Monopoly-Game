#include "DesignToPlay.h"
#include "Input.h"
#include "Output.h"
#include"Grid.h"
#include "Player.h"
DesignToPlay::DesignToPlay(ApplicationManager* pApp) :Action(pApp) {


}
void DesignToPlay::ReadActionParameters()
{

}

void DesignToPlay::Execute() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->CreatePlayModeToolBar();
}