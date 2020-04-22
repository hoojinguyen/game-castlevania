#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Tile.h"
#include "TextureManager.h"
#include "GTexture.h"
#include "GSprite.h"
#include "define.h"

#include "Camera.h"
using namespace std;

class TileMap
{
private:
	Tile** matrix;
	GTexture* _texture;
	GSprite* sprite;

	int rows;
	int cols;
	float width;
	float height;
	float tileWidth;
	float tileHeight;
	int spritePerRow;
	
	void LoadListTile(string file);
public:
	TileMap(float _width, float _height, eType type, string pathFile);
	~TileMap();
	void Render(int screenWidth, int screenHeight, Camera* camera);
	void Unload();
};

