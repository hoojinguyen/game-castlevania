﻿#ifndef CSPRITE_H
#define CSPRITE_H

#include "GTexture.h"

class GSprite {
private:
	LPD3DXSPRITE spriteHandler;
	int currentFrame;
	int totalFrames;

public:
	GSprite(GTexture* Texture, DWORD TimeAnimation);
	virtual ~GSprite();

	GTexture* texture;

	DWORD timeAccumulated;	 // thời gian chờ đã tích lũy
	DWORD timeAnimation; // thời gian phải chờ giữa các frame

	RECT GetRectFrame(int idFrame);

	void Next(); //sang frame tiếp theo
	void ResetTime(); //trở về frame đầu tiên

	void SelectFrame(int idFrame); //chọn ID của 1 frame
	
	void Update(DWORD dt); //update animation

	void Draw(float X, float Y, int alpha = 255, int R = 255, int G = 255, int B = 255); // Render current sprite at location (X,Y) at the target surface
	void DrawFrame(int idFrame, float X, float Y, int alpha = 255, int R = 255, int G = 255, int B = 255);

	void DrawFlipX(float X, float Y, int alpha = 255, int R = 255, int G = 255, int B = 255); //Render with scale (-1, 1)
	void DrawFrameFlipX(int idFrame, float X, float Y, int alpha = 255, int R = 255, int G = 255, int B = 255);

	int GetCurrentFrame();
	int GetTotalFrames();
};

#endif