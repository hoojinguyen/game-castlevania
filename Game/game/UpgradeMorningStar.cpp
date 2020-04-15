#include "UpgradeMorningStar.h"

UpgradeMorningStar::UpgradeMorningStar(float X, float Y)
{
	texture = TextureManager::GetInstance()->GetTexture(eType::UPGRADEMORNINGSTAR);
	sprite = new GSprite(texture, 100);
	type = eType::UPGRADEMORNINGSTAR;

	this->x = X;
	this->y = Y;
	vy = UPGRADEMORNINGSTAR_GRAVITY;

	TimeDisplayed = 0;
	TimeDisplayMax = UPGRADEMORNINGSTAR_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeWaited = 0;
	TimeWaitMax = UPGRADEMORNINGSTAR_TIMEWAITMAX;

}

void UpgradeMorningStar::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + texture->GetFrameWidth();
	bottom = y + texture->GetFrameHeight();
}

UpgradeMorningStar::~UpgradeMorningStar()
{
}
