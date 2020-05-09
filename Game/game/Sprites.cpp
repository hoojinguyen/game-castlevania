#include "Sprites.h"
#include "Game.h"
#include "Utils.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, int dx, int dy)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;

	this->texture = tex;

	this->dx = dx;
	this->dy = dy;
}


CSprites* CSprites::__instance = NULL;

CSprites* CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y, int alpha, int r, int g, int b)
{
	CGame::GetInstance()->Draw(x + dx, y + dy, texture, left, top, right, bottom, alpha, r, g, b);
}

void CSprite::Draw(float x, float y, RECT rect, int alpha, int r, int g, int b)
{
	CGame::GetInstance()->Draw(x + dx, y + dy, texture, rect, alpha, r, g, b);
}

void CSprite::DrawWithoutCamera(float x, float y, int alpha, int r, int g, int b)
{
	CGame::GetInstance()->DrawWithoutCamera(x + dx, y + dy, texture, left, top, right, bottom, alpha, r, g, b);
}

void CSprite::DrawWithoutCamera(float x, float y, RECT rect, int alpha, int r, int g, int b)
{
	CGame::GetInstance()->DrawWithoutCamera(x + dx, y + dy, texture, rect, alpha, r, g, b);
}


void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, int dx, int dy)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex, dx, dy);
	sprites[id] = s;

	DebugOut(L"[INFO] sprite added: %d, %d, %d, %d, %d, %d, %d \n", id, left, top, right, bottom, dx, dy);
}

void CSprites::AddByWidthHeight(int id, int left, int top, int width, int height, LPDIRECT3DTEXTURE9 tex, int dx, int dy)
{
	LPSPRITE s = new CSprite(id, left, top, left + width, top + height, tex, dx, dy);
	sprites[id] = s;

	DebugOut(L"[INFO] sprite added: %d, %d, %d, %d, %d, %d, %d \n", id, left, top, left + width, top + height, dx, dy);
}


LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}

/*
	Clear all loaded textures
*/
void CSprites::Clear()
{
	for (auto x : sprites)
	{
		LPSPRITE s = x.second;
		delete s;
	}

	sprites.clear();
}

void CSprites::Clear(vector<int> listId)
{
	for (size_t i = 0; i < listId.size(); i++)
	{
		LPSPRITE s = Get(listId.at(i));

		delete s;
		sprites.erase(listId.at(i));
	}
}
