#pragma once
#include "Effect.h"

class MoneyEffect : public Effect
{
	int moneyType;

public:
	MoneyEffect(int _moneyType);
	~MoneyEffect();
	void Update(DWORD dt);
	void Render();
	void Enable();
};

