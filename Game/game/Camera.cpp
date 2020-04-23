#include "Camera.h"

CCamera* CCamera::__instance = NULL;

CCamera* CCamera::GetInstance()
{
	if (__instance == NULL) __instance = new CCamera(0, 0);
	return __instance;
}


CCamera::CCamera(float x, float y)
{
	this->cameraPosition.x = x;
	this->cameraPosition.y = y;
	this->cameraPosition.z = 0;
}


CCamera::~CCamera()
{
}

D3DXVECTOR3 CCamera::GetPositionInCamera(D3DXVECTOR3 position)
{
	D3DXVECTOR3 pos;
	pos.x = position.x - this->cameraPosition.x;
	pos.y = position.y - this->cameraPosition.y;
	return D3DXVECTOR3(pos.x, pos.y, 0);
}

void CCamera::SetCameraPosition(float x, float y)
{
	this->cameraPosition.x = x;
	this->cameraPosition.y = y;
}

D3DXVECTOR3 CCamera::GetCameraPosition()
{
	return this->cameraPosition;
}
