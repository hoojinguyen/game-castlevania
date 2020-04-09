#include "Grid.h"
 
Grid::Grid()
{

}
 
Grid::~Grid()
{
	
}

void Grid::SetFile(char * filename)
{
	listObjectGame.clear(); 
	int i, j; 

	ifstream inp;
	inp.open(filename, ios::in);
	 
	int id, type, direction;
	float x, y, w, h;

	if (inp)
	{
		while (inp >> id >> type >> direction >> x >> y >> w >> h)
		{
			Insert(id, type, direction, x, y, w, h);
		}
		inp.close();
	} 
}

void Grid::Insert(int id, int type, int direction, float x, float y, float w, float h)
{ 
	int Top = floor( y / (float)GRID_CELL_HEIGHT);
	int Bottom = floor((y + h) / (float)GRID_CELL_HEIGHT);

	int Left = floor(x / (float)GRID_CELL_WIDTH);
	int Right = floor((x+w) / (float)GRID_CELL_WIDTH);

	GameObject * obj = GetNewObject(type, x, y, w, h); 
	if (obj == NULL)
	{
		DebugOut(L"[Insert Object GRID Fail] : Khong tao duoc object!\n");
		return;
	} 
	obj->SetId(id);
	obj->SetDirection(direction);
	obj->isTake = false;

	listObjectGame.push_back(obj);

	for (int row = Top; row <= Bottom; row++)
	{
		for (int col = Left; col <= Right; col++)
		{
			cells[row + GRID_BASE][col + GRID_BASE].push_back(obj);
		}
	}

}

GameObject * Grid::GetNewObject(int type, int x, int y,int w, int h)
{
	if (type == eType::BRICK) return new Brick(x, y, w, h);
	if (type == eType::TORCH) return new Torch(x, y);
	return NULL;
}

void Grid::GetListObject(vector<Object*>& ListObj, Camera * camera)
{
	ListObj.clear(); // clear list
	ResetTake();

	int rowBottom = floor((camera->GetViewport().y + camera->GetHeight()) / (float)GRID_CELL_HEIGHT);
	int rowTop = floor((camera->GetViewport().y) / (float)GRID_CELL_HEIGHT);

	int colLeft = floor((camera->GetViewport().x) / (float)GRID_CELL_WIDTH);
	int colRight = floor((camera->GetViewport().x + camera->GetWidth()) / (float)GRID_CELL_WIDTH);


	for (int row = rowTop; row <= rowBottom; row++)
		for (int col = colLeft; col <= colRight; col++)
		{
			for (int i = 0; i < cells[row + GRID_BASE][col + GRID_BASE].size(); i++)
			{
				if (cells[row + GRID_BASE][col + GRID_BASE].at(i)->GetHealth() > 0) // còn tồn tại
				{
					if (cells[row + GRID_BASE][col + GRID_BASE].at(i)->isTake == false)
					{
						ListObj.push_back(cells[row + GRID_BASE][col + GRID_BASE].at(i));
						cells[row + GRID_BASE][col + GRID_BASE].at(i)->isTake = true;
					}
				}
			}
		}
}

void Grid::GetListObject(vector<Object*> &ListObj, GameObject * obj)
{
	ListObj.clear(); // clear list
	ResetTake();

	int rowBottom = floor((obj->GetY() + obj->GetHeight()) / (float)GRID_CELL_HEIGHT);
	int rowTop = floor((obj->GetY()) / (float)GRID_CELL_HEIGHT);

	int colLeft = floor((obj->GetX()) / (float)GRID_CELL_WIDTH);
	int colRight = floor((obj->GetX() + obj->GetWidth()) / (float)GRID_CELL_WIDTH);


	for (int row = rowTop; row <= rowBottom; row++)
		for (int col = colLeft; col <= colRight; col++)
		{
			for (int i = 0; i < cells[row + GRID_BASE][col + GRID_BASE].size(); i++)
			{
				if (cells[row + GRID_BASE][col + GRID_BASE].at(i)->GetHealth() > 0) // còn tồn tại
				{
					if (cells[row + GRID_BASE][col + GRID_BASE].at(i)->isTake == false)
					{
						ListObj.push_back(cells[row + GRID_BASE][col + GRID_BASE].at(i));
						cells[row + GRID_BASE][col + GRID_BASE].at(i)->isTake = true;
					}
				}
			}
		}
}

void Grid::ResetTake()
{
	for (int i = 0; i < listObjectGame.size(); i++)
	{
		listObjectGame[i]->isTake = false;
	}
}
 