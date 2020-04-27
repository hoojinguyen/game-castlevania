#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include "Sprites.h"

class Tile
{
	int id;
	RECT bound;
	D3DXVECTOR2 position;
	LPSPRITE sprite;
	CCamera* camera;

public:
	Tile();
	~Tile();
	Tile(int _id, RECT _bound, D3DXVECTOR2 _position);

	void Render();

	bool CheckInBoundCamera(int screenWidth, int screenHeight);

	int GetID() { return id; }
	void setID(int _id);

	RECT GetBound() { this->bound; }
	void SetBound(RECT _bound);

	D3DXVECTOR2 GetPosision() { return this->position; }
	void SetPosition(D3DXVECTOR2 _position);

	void SetSprite(LPSPRITE _sprite);
};

class Tile;
typedef Tile* LPTILE;

