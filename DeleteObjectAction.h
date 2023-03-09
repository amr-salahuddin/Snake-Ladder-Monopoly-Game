#pragma once
#include"Action.h"
#include"CellPosition.h"
//Added class
class DeleteObjectAction:public Action
{
private :
	CellPosition destination; // cell to delete from
public:

	DeleteObjectAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads deleteObjectAction action parameters (startPos, endPos)

	virtual void Execute(); // Creates a new Ladder Object 
							// then Sets this Ladder object to the GameObject Pointer of its Cell


	virtual ~DeleteObjectAction(); // Virtual Destructor

};

