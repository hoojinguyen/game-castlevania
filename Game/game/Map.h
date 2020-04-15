#ifndef __MAP_H__
#define __MAP_H__

#include "TextureManager.h"
#include "GTexture.h"
#include "GSprite.h"
#include "define.h"

#include "Camera.h"

#define TILE_FRAME_WIDTH 64
#define TILE_FRAME_HEIGHT 64

class Map
{
private:
	GTexture* _texture;
	GSprite* _sprite;

	int ScreenColumn;
	int ScreenRow;

	int ColumnMap; // số lượng dòng của ma trận tilemap txt
	int RowMap;// số lượng cột của ma trận tilemap txt

	int ColumnTile; // số lượng cột tile trong texture
	int RowTile;// số lượng dòng tile trong texture
	int TotalTiles; // tổng số lương tile trong texture 

	int HeightBoard; // chiều cao board

	int TileMap[500][500];


public:
	Map();
	~Map();
	void LoadMap(eType type);
	void ReadMapTXT(char* filename);
	void DrawMap(Camera* camera);

	int GetMapWidth();
	int GetMapHeight();
};




#endif