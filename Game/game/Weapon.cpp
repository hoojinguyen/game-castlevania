#include "Weapon.h"

Weapon::Weapon()
{
	isFinish = 1;
}


Weapon::~Weapon()
{ 
}

int Weapon::GetDirection()
{
	return direction;
}

void Weapon::SetDirection(int d)
{
	this->direction = d;
}

void Weapon::Attack(float X, float Y, int Direction)
{
	this->x = X;
	this->y = Y;
	this->direction = Direction;
	isFinish = false; // chưa kết thúc


	LastTimeAttack = GetTickCount(); // lưu lại thời điểm lúc vừa tấn công, làm đánh dấu tránh 1 hit đánh nhiều lần cho các object, có health >1.
}

void Weapon::Render(Camera* camera)
{
	if (isFinish)
		return;

	//DebugOut(L"WEAPON: index = %d \n", sprite->GetCurrentFrame());
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == -1)
		sprite->Draw(pos.x, pos.y);
	else
		sprite->DrawFlipX(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}
 
bool Weapon::GetFinish()
{
	return isFinish;
}

void Weapon::SetFinish(bool finish)
{
	isFinish = finish;
}

DWORD Weapon::GetLastTimeAttack()
{
	return LastTimeAttack;
}
 
bool Weapon::isCollision(GameObject* obj)
{
	if (isFinish == true)
		return false;

	// dt, dx, dy đã update 
	if (obj->GetHealth() <= 0) // vật này die rồi thì ko va chạm
		return false;
	return isCollitionObjectWithObject(obj);
}

void Weapon::UpdatePositionFitSimon()
{
}
