#include "Cell.h"

Cell::Cell()
{
	listObj.clear();
}


Cell::~Cell()
{

}

void Cell::Insert(LPGAMEOBJECT object)
{
	listObj.push_back(object);
}

void Cell::Unload()
{
	//for (int i = 0; i < listObj.size(); i++)
	//	delete listObj[i];
	listObj.clear();
}
