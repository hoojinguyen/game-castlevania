#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include "TextureManager.h"
#include "GTexture.h"
#include "GSprite.h"
#include "define.h"

#include "Camera.h"
class Tile
{
	int id;
	RECT bound;
	D3DXVECTOR2 position;
	GSprite* sprite;
	Camera* camera;
public:
	Tile();
	~Tile();
	Tile(int _id, RECT _bound, D3DXVECTOR2 _position);
	void setID(int _id);
	void SetPosition(D3DXVECTOR2 _position);
	void SetBound(RECT _bound);
	void SetSprite(GSprite* _sprite);
	int GetId() { return id; }
	D3DXVECTOR2 GetPosision() { return this->position; }
	RECT GetBound() { this->bound; }
	void Render();
	bool CheckInBoundCamera(int screenWidth, int screenHeight);
};

class Tile;
typedef Tile* LPTILE;

