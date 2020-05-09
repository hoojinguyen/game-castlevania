#pragma once
#include "GameObject.h"

class Item;
typedef Item* LPITEM;
class Item : public CGameObject
{
	int typeItem;

	DWORD timeStartEnable;
	bool isGround;
	bool isFirstTime;

	DWORD TimeDisplayMax; // thời gian tối đa cho phép hiển thị.
	DWORD TimeDisplayed; // Thời gian đã hiển thị.

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
};

