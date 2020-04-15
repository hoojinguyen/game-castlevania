#ifndef _DEFINE_H__
#define _DEFINE_H__
#define _USE_MATH_DEFINES

#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h> 
#include <dinput.h> 
#include <stdio.h>
#include "debug.h"

#include <algorithm>

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

#include <map>
#include <vector>

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 448

#define SCREEN_WIDTH 528
#define SCREEN_HEIGHT 480

#define COLOR_BLACK D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)  
#define COLOR_KEY D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f) 

#define SHOWBOX_PINK 0
#define IS_DEBUG_RENDER_BBOX 1

using namespace std;
 
extern int Window_Width;
extern int Window_Height;

extern int MapWidth;
extern int MapHeight;

extern int ScreenColumn;
extern int ScreenRow;

// ID của Sprite, object
enum eType
{
	SIMON = 01,
	SIMON_TRANS = 02,
	SIMON_DEADTH = 03,

	// object nền
	BRICK = 21,
	TEX_BRICK_MODEL_1 = 22,
	TEX_BRICK_MODEL_2 = 23,
	TEX_BRICK_MODEL_3 = 24,
	TEX_BRICK_TRANSPARENT = 25,
	GATE = 26,
	TEX_BRICK_MODEL_3_3_32 = 27,
	TEX_BRICK_MODEL_3_4_32 = 28,

	// object
	OBJECT_HIDDEN = 42,
	TORCH = 41,
	CANDLE = 43,
	STAIR = 44,
	STAIR_BOTTOM = 47,
	STAIR_TOP = 48,

	// weapon
	MORNINGSTAR = 61,

	// item
	LARGEHEART = 81,
	UPGRADEMORNINGSTAR = 82,

	// other
	MAP1 = 104,
	RENDERBBOX = 105,

};


 
enum eDirection
{
	NONE = 0,
	TOP = (1 << 0),
	LEFT = (1 << 1),
	RIGHT = (1 << 2),
	BOTTOM = (1 << 3)
};
 
typedef D3DXVECTOR3 GVector3;
typedef D3DXVECTOR2 GVector2;
#define VECTOR2ZERO GVector2(0.0f, 0.0f)
//
//void GLTrace(char* format, ...)
//{
//	char *_traceFile = "C:\\Temp\\Sample_TH_game.log";
//	int _traceNum = 1;
//
//	if (!_traceNum) return;
//
//	FILE *f = stderr;
//	if (_traceFile != NULL)
//	{
//		if (fopen_s(&f, _traceFile, "a") != 0)
//		{
//			fprintf(stderr, "WARNING: Failed to open trace file '%s' for writing!\n", _traceFile);
//			return;
//		}
//	}
//	va_list ap;
//	va_start(ap, format);
//	fprintf(f, format, ap);
//	va_end(ap);
//	fprintf(f, "\n");
//	if (_traceFile != NULL) fclose(f);
//}
//
//void GLMessage(char* text)
//{
//	//	Game::GetInstance()->
//		//MessageBoxA(G_hWnd, text, "Sample TH", MB_OK);
//}
//
//void GLTitle(char* text) {
//	//SetWindowTextA(G_hWnd, text);
//}
//
//void OutDebug(const char * text)
//{
//	OutputDebugStringA(text);
//	OutputDebugStringA("\n");
//
//}
//

#ifndef CHECK_OBJECT_IN_CAMERA // Kiểm tra GameObject có nằm trong camera ko?
#define CHECK_OBJECT_IN_CAMERA(obj) \
checkObjectInCamera(obj->GetX(), obj->GetY(), (float)obj->GetWidth(),  (float)obj->GetHeight())
#endif


#ifndef SAFE_DELETE
#define SAFE_DELETE(ptr) \
if(ptr) \
{\
	delete (ptr); \
	ptr = nullptr; \
} \

#endif

#endif // !_DEFINE_H__


