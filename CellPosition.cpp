#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition()
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;
}

CellPosition::CellPosition(int v, int h)
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition(int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
												// from the passed (cellNum)
												// (*this) = ... --> this will copy the returned (vCell and hCell)
												//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v)
{
	///TODO: Implement this function as described in the .h file (don't forget the validation)
	bool vBool = (v >= 0 && v <= 8);
	if (vBool)
	{
		vCell = v;
		return true;
	}
	else
		vCell = -1;
	return false; // this line sould be changed with your implementation
}

bool CellPosition::SetHCell(int h)
{
	///TODO: Implement this function as described in the .h file (don't forget the validation)
	bool hBool = (h >= 0 && h <= 10);
	if (hBool)
	{
		hCell = h;
		return true;
	}
	else
		hCell = -1;
	return false; // this line sould be changed with your implementation
}

int CellPosition::VCell() const
{
	return vCell;
}

int CellPosition::HCell() const
{
	return hCell;
}

bool CellPosition::IsValidCell() const
{
	///TODO: Implement this function as described in the .h file
	bool vBool = vCell >= 0 && vCell < 9;
	bool hBool = hCell >= 0 && hCell < 11;
	if (vBool && hBool)
		return true;
	return false; // this line sould be changed with your implementation
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
										  // which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition& cellPosition)
{
	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it

	///TODO: Implement this function as described in the .h file
	//return (NumVerticalCells - cellPosition.VCell()) * (1 + cellPosition.HCell());
	if (cellPosition.IsValidCell()) {
		int tmp = (NumVerticalCells - cellPosition.VCell() - 1) * 11 + (cellPosition.HCell() + 1);
		if (tmp >= 1 && tmp <= 99)
			return tmp;
		//()
	}
	return -1; // this line should be changed with your implementation
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;

	/// TODO: Implement this function as described in the .h file
	if (cellNum == 99)
	{
		position.SetHCell(10);
		position.SetVCell(0);
	}
	else if (cellNum % 11 == 0) // rightmost cell
	{
		position.SetHCell(10);
		position.SetVCell(9 - cellNum / 11);
	}
	else
	{
		position.SetHCell(cellNum % 11 - 1); //  
		position.SetVCell(8 - cellNum / 11); // numvertical -1 
	}

	if (position.IsValidCell())
		return position;
	else
		return CellPosition();
	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it


}

void CellPosition::AddCellNum(int addedNum)
{

	/// TODO: Implement this function as described in the .h file

	int currentNum = GetCellNumFromPosition(*this);
	CellPosition tmp = GetCellPositionFromNum(currentNum + addedNum);
	if (tmp.IsValidCell())
		*this = tmp;
	// make a temporary instance of cell position class to check whether cell position after addition is valid or not before adding it to the original instance

	// Note: this function updates the data members (vCell and hCell) of the calling object

}