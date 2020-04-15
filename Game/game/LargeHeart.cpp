#include "LargeHeart.h"

LargeHeart::LargeHeart(float X, float Y)
{
	type = eType::LARGEHEART;
	texture = TextureManager::GetInstance()->GetTexture(type);
	sprite = new GSprite(texture, 100);

	this->x = X;
	this->y = Y;
	vy = LARGEHEART_GRAVITY;
	TimeDisplayMax = LARGEHEART_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;
	TimeWaited = 0;
	TimeWaitMax = LARGEHEART_TIMEWAITMAX;
}

void LargeHeart::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + texture->GetFrameWidth();
	bottom = y + texture->GetFrameHeight();
}


LargeHeart::~LargeHeart()
{
}