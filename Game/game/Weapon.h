#pragma once
#include "GameObject.h"
class Weapon : public CGameObject
{
protected:
	int useHeart;
	int damage;
	int count;
	float speed;

public:
	Weapon();
	~Weapon();

	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	int GetUseHeart() { return useHeart; }

	int GetDamage() { return damage; }
	void SetDamage(int damage) { this->damage = damage; }

	void ResetAnimation();
};

