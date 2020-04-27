#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "Game.h"

using namespace std;

class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;

	int dx;
	int dy;

	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, int dx = 0, int dy = 0);

	void Draw(float x, float y, int alpha = 255);
	void Draw(float x, float y, int left, int top, int right, int bottom, int alpha = 255);
	void DrawWithoutCamera(float x, float y, int alpha = 255);
	void DrawWithoutCamera(float x, float y, int left, int top, int right, int bottom, int alpha = 255);
	int getLeft() { return left; }
	int getTop() { return top; }
	int getRight() { return right; }
	int getBottom() { return bottom; }
};

typedef CSprite* LPSPRITE;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites* __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, int dx = 0, int dy = 0);
	void AddByWidthHeight(int id, int left, int top, int width, int height, LPDIRECT3DTEXTURE9 tex, int dx = 0, int dy = 0);
	LPSPRITE Get(int id);
	void Clear();
	void Clear(vector<int> listId);

	static CSprites* GetInstance();
};
