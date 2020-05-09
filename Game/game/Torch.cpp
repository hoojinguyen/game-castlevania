#include "Torch.h"

Torch::Torch()
{
	collisionEffect = new CollisionEffect();
	deadEffect = new DeadEffect();

	isEnable = true;
}

void Torch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 16;
	b = y + 32;
}

void Torch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (isEnable)
	{
		collisionEffect->SetPosition(x, y + 10);
		deadEffect->SetPosition(x + 3, y - 3);
	}

	collisionEffect->Update(dt);
	deadEffect->Update(dt);
}

void Torch::Render()
{
	if (isEnable)
	{
		animation_set->at(0)->Render(x, y);
		RenderBoundingBox();
	} 
	collisionEffect->Render();
	deadEffect->Render();
}