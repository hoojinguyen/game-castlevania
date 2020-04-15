#ifndef __CTEXTURE_H__
#define __CTEXTURE_H__
 
#include "Game.h"
#include "define.h"

class GTexture 
{

private:
	int Column;		//số cột frame
	int Row;		//số hàng frame
	int Count;		//tổng số frame
	int FrameWidth;		//width of 1 frame
	int FrameHeight;	//height of 1 frame

public:
	int TotalFrames;
	LPDIRECT3DTEXTURE9 Texture;

	GTexture(char* filePath, int column = 1, int row = 1, int totalframes = 1, int R = 255, int G = 0, int B = 255);
	~GTexture();

	int GetFrameWidth();
	int GetFrameHeight();
	int GetColumn();
	int GetRow();

};

#endif