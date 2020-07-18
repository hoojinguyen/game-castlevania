#pragma once
#include "GameObject.h"
#include "MoneyEffect.h"

class Item;
typedef Item* LPITEM;
class Item : public CGameObject
{
	int typeItem;

	bool isGround;
	bool isFirstTime;

	DWORD timeStartEnable;
	DWORD TimeDisplayMax; // thời gian tối đa cho phép hiển thị.
	DWORD TimeDisplayed; // Thời gian đã hiển thị.

	MoneyEffect* moneyEffect;

	void Init();
	void RandomType();
	void RandomItem();
	void RandomWeapon();

public:
	Item();
	Item(int typeItem);
	~Item();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	int GetTypeItem() { return typeItem; }

	void TurnOnTimeStartEnable();

	MoneyEffect* GetMoneyEffect() { return moneyEffect; }
};

