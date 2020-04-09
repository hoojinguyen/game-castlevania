#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "define.h"

class Camera
{
protected:
	D3DXVECTOR2 _viewport;
	int _width;
	int _height;

	/*int _borderLeft;
	int _borderRight;*/

public:
	Camera(int w, int h/*, int b_left, int b_right*/);
	~Camera();

	int GetWidth();
	int GetHeight();
	D3DXVECTOR2 GetViewport();
	D3DXVECTOR2 Transform(float x, float y);

	void SetPosition(int x, int y);
	 
	void Update();
};

#endif



