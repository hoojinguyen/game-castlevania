#pragma once
#include "GameObject.h"
class Weapon : public CGameObject
{
protected:
	int useHeart;
	int damage;
	int count;
public:
	Weapon();
	~Weapon();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void ResetAnimation();
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int GetUseHeart() { return useHeart; }
	int GetDamage() { return damage; }
	void SetDamage(int damage) { this->damage = damage; }
};

