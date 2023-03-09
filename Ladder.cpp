#include "Ladder.h"
#include"CellPosition.h"
#include"Snake.h"
Ladder::Ladder(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;

	///TODO: Do the needed validation
}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click
	pGrid->GetOutput()->PrintMessage("You have reached a ladder, Click to continue ");
	pGrid->GetInput()->GetCellClicked();
	pGrid->GetOutput()->ClearStatusBar();
	// 2- Apply the ladder's effect by moving the player to the endCellPos
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);
	//    Review the "pGrid" functions and decide which function can be used for that
}
//Added
bool Ladder::IsOverlapping(GameObject* newobj)
{
	int start_of_me = GetPosition().GetCellNum();
	int end_of_me = GetEndPosition().GetCellNum();
	if (newobj != NULL)
	{
		if (dynamic_cast<Ladder*>(newobj))
		{
			int start_y_of_me = GetPosition().VCell();
			int start_y_of_passed = dynamic_cast<Ladder*>(newobj)->GetPosition().VCell();
			int end_y_of_me = GetEndPosition().VCell();
			int end_y_of_passed = dynamic_cast<Ladder*>(newobj)->GetEndPosition().VCell();
			int x_of_me = GetPosition().HCell();
			int x_of_passed = dynamic_cast<Ladder*>(newobj)->GetPosition().HCell();
			if (x_of_me == x_of_passed)
			{
				if (start_y_of_me == start_y_of_passed || end_y_of_me == end_y_of_passed||end_y_of_me==start_y_of_passed)
					return true;
				if ((end_y_of_me < end_y_of_passed) && (start_y_of_me > end_y_of_me))
					return true;
				if((end_y_of_passed<end_y_of_me)&&(start_y_of_passed>start_y_of_me))
					return true;
			}
		}
		else if (dynamic_cast<Snake*>(newobj))
		{
			int snake_start_cell = dynamic_cast<Snake*>(newobj)->GetPosition().GetCellNum();
			if (snake_start_cell == end_of_me)
				return true;
		}
		return false;
	}
}
CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}
void Ladder::Save(ofstream& OutFile)
{
	OutFile << position.GetCellNum() << " " << endCellPos.GetCellNum()<<endl;
}
void Ladder::Load(ifstream& Infile)
{
	int start, end;
	Infile >> start >> end;
	CellPosition cp;
	position = cp.GetCellPositionFromNum(start);
	endCellPos = cp.GetCellPositionFromNum(end);
}
Ladder::~Ladder()
{
}
