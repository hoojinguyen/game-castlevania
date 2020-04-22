#include "TileMap.h"
#include "Camera.h"
#include "Utils.h"

using namespace std;

TileMap::TileMap(float _width, float _height, eType type,  string pathFile)
{
	width = _width;
	height = _height;
	//sprite = _sprite;

	_texture = TextureManager::GetInstance()->GetTexture(type);
	sprite = new GSprite(_texture, 100);

	this->LoadListTile(pathFile);
}


TileMap::~TileMap()
{

}

void TileMap::LoadListTile(string pathFile)
{
	fstream pFile;
	pFile.open(pathFile, fstream::in);
	string lineString;

	vector<string> tokens;

	pFile.good();
	getline(pFile, lineString);
	tokens = split(lineString, " ");
	rows = atoi(tokens[0].c_str());
	cols = atoi(tokens[1].c_str());

	matrix = new LPTILE[rows];

	for (int i = 0; i < rows; i++)
		matrix[i] = new Tile[cols];

	pFile.good();
	getline(pFile, lineString);
	tokens = split(lineString, " ");
	tileWidth = atoi(tokens[0].c_str());
	tileHeight = atoi(tokens[1].c_str());

	pFile.good();
	getline(pFile, lineString);
	spritePerRow = atoi(lineString.c_str());

	for (int i = 0; i < rows; i++)
	{
		pFile.good();
		getline(pFile, lineString);
		tokens = split(lineString, " ");
		for (int j = 0; j < cols; j++)
		{
			RECT bound;
			D3DXVECTOR2 position;
			int id = atoi(tokens[j].c_str());
			matrix[i][j].setID(id);

			bound.top = (id / spritePerRow) * tileHeight;
			bound.left = (id % spritePerRow) * tileWidth;
			bound.right = bound.left + tileWidth;
			bound.bottom = bound.top + tileHeight;

			position.x = j * tileWidth;
			position.y = i * tileHeight;
			matrix[i][j].SetBound(bound);
			matrix[i][j].SetPosition(position);
			matrix[i][j].SetSprite(sprite);

			//DebugOut(L"[INFO] tile add: %d, %d, %d, %d, %d, %f, %f \n", id, bound.left, bound.top, bound.right, position.x, position.y);
		}
	}

	pFile.close();
}


void TileMap::Render(int screenWidth, int screenHeight, Camera* camera)
{
	int rowStart;
	int rowEnd;
	int colStart;
	int colEnd;

	if ((camera->GetYCam() / tileHeight) < 0)
		rowStart = 0;
	else
		rowStart = (camera->GetYCam() / tileHeight);

	if (((camera->GetYCam() / tileHeight + screenHeight / tileHeight) + 1) > rows)
		rowEnd = rows;
	else
		rowEnd = ((camera->GetYCam() / tileHeight + screenHeight / tileHeight) + 1);

	if ((camera->GetXCam() / tileWidth) < 0)
		colStart = 0;
	else
		colStart = (camera->GetXCam() / tileWidth);

	if (((camera->GetXCam() / tileWidth + screenWidth / tileWidth) + 1) > cols)
		colEnd = cols;
	else
		colEnd = ((camera->GetXCam() / tileWidth + screenWidth / tileWidth) + 1);

	for (int i = rowStart; i < rowEnd; i++)
	{
		for (int j = colStart; j < colEnd; j++)
		{
			matrix[i][j].Render();
		}
	}

	/*for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (matrix[i][j].CheckInBoundCamera(screenWidth, screenHeight))
			{
				matrix[i][j].Render();
			}
		}
	}*/
}



void TileMap::Unload()
{
	if (matrix)
	{
		/*for (int i = 0; i < rows; i++)
		{
			delete matrix[i];
		}*/
		//delete matrix;
		//matrix = nullptr;
	}

	if (sprite)
	{
		sprite = nullptr;
	}
}
