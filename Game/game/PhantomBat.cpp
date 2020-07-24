#include <time.h>
#include "Define.h"

#include "PhantomBat.h"
#include "Simon.h"

PhantomBat::PhantomBat(float startX, float startY)
{
	this->startX = startX;
	this->startY = startY;

	this->hp = PHANTOM_BAT_HP;
	isEnable = true;

	damage = PHANTOM_BAT_DAMAGE;

	Enemy::Enemy();

	SetState(PHANTOM_BAT_STATE_IDLE);

	point = 200;

	bossDeadEffect = new BossDeadEffect(1);
	point = 3000;
	srand(time(0));
	isFlyToRandomPos = true;
	isFlyToSimonPos = true;

	point = 3000;
	waitTime = 0;
	hurtTime = PHANTOM_BAT_HURT_TIME;
	isHurted = false;
	vx = 0.125;
	vy = 0.120;
	nx = 0;
	ny = 0;

	previousHP = hp;
	introTime = 2000;
	simonPos.x = -1;
	distance = -1;
}

PhantomBat::~PhantomBat()
{

}

void PhantomBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);

	if (isEnable)
	{
		if (Intro(dt) == true)
			return;
		CheckHPChange();
		if (isHurted == true)
			CheckHurtTime(dt);
		else
		{
			if (isFlyToRandomPos == true) {
				if (waitTime > 0)
					waitTime -= dt;
				else
				{
					Fly(dt);
				}
			}
			else if (isFlyToSimonPos == false) {
				if (isFlyToRandomPos == false)
					FlyToRandomPos(dt);
				else if (isFlyToRandomPos == true)
					RandomPos();
			}
		}
	}

	if (!isEnable)
	{
		delayTime += dt;
		if (delayTime > 1500)
			bossDeadEffect->Update(dt);
	}

	collisionEffect->SetPosition(x, y + 10);
	collisionEffect->Update(dt);
}

void PhantomBat::Render()
{
	if (!isDeadth && isEnable) {
		int posX = x, posY = y;
		int ani = 0;
		switch (state)
		{
		case PHANTOM_BAT_STATE_IDLE:
		{
			ani = PHANTOM_BAT_ANI_IDLE;
		}
		break;
		case PHANTOM_BAT_STATE_FLYING:
		{
			ani = PHANTOM_BAT_ANI_FLYING;
		}
		break;
		default:
			break;
		}

		animation_set->at(ani)->Render(posX, posY);
		RenderBoundingBox();
	}
	collisionEffect->Render();

	Enemy::Render();

}

void PhantomBat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isDeadth) {
		left = 0;
		top = 0;
		right = left + 0;
		bottom = top + 0;
	}
	else {
		if (state == PHANTOM_BAT_STATE_FLYING) {
			left = x;
			top = y;
			if (animation_set->at(0)->GetCurrentFrame() == 0) {
				right = left + 48;
				bottom = top + 22;
			}
			else if (animation_set->at(0)->GetCurrentFrame() == 1) {
				right = left + 32;
				bottom = top + 23;
			}
		}
		else {
			left = 0;
			top = 0;
			right = left + 0;
			bottom = top + 0;
		}
	}
}

void PhantomBat::SetState(int state)
{
	Enemy::SetState(state);
}

void PhantomBat::CalculateSimonPos(DWORD dt)
{
	float simonX, simonY;

	Simon::GetInstance()->GetPosition(simonX, simonY);

	if (simonPos.x < 0) {
		simonPos = D3DXVECTOR2(simonX, simonY);
	}
	else if (chaseTime > 0) {
		chaseTime -= dt * 0.001;
		simonPos = D3DXVECTOR2(simonX, simonY);
	}

	if (isFlyToSimonPos == true)
	{
		distance = sqrt(
			pow(simonPos.x - x, 2) +
			pow(simonPos.y - y, 2));

		nx = (simonPos.x - x) / distance;
		ny = (simonPos.y - y) / distance;
	}
	if (isFlyToSimonPos == false)
	{
		batPos = D3DXVECTOR2(x, y);
	}
}

void PhantomBat::Fly(DWORD dt)
{
	if (abs(batPos.x - simonPos.x) > 200)
	{
		vx = 0.23;
		vy = 0.18;
	}
	x += nx * vx * dt;
	y += ny * vy * dt;

	if (sqrt(pow(simonPos.x - x, 2) + pow(simonPos.y - y, 2)) >= distance)
	{
		isFlyToSimonPos = false;
		x = simonPos.x;
		y = simonPos.y;
	}
	this->SetPosition(x, y);
	SetState(PHANTOM_BAT_STATE_FLYING);
}

void PhantomBat::RandomPos()
{
	random.x = rand() % (400) + 5100;
	random.y = rand() % (50) + 120;
	isFlyToRandomPos = false;
	waitTime = PHANTOM_BAT_WAIT_TIME;
	vx = 0.125;
	vy = 0.12;
}

bool PhantomBat::Intro(DWORD dt)
{
	if (introTime > 0)
	{
		if (introTime > 1500)
			SetState(PHANTOM_BAT_STATE_IDLE);
		else
			SetState(PHANTOM_BAT_STATE_FLYING);
		introTime -= dt;
		return true;
	}
	else
		return false;
}

void PhantomBat::CheckHPChange()
{
	if (previousHP != hp)
	{
		if (hp <= 0)
		{

			isEnable = false;
			isDeadth = true;
			bossDeadEffect->Enable();
			return;
		}
		else
		{
			isHurted = true;
			previousHP = hp;
			return;
		}
	}
}

void PhantomBat::CheckHurtTime(DWORD dt)
{
	SetState(PHANTOM_BAT_STATE_HURT);
	hurtTime -= dt;
	if (hurtTime <= 0)
	{
		isHurted = false;
		hurtTime = PHANTOM_BAT_HURT_TIME;
	}
}

void PhantomBat::FlyToRandomPos(DWORD dt)
{
	distance = sqrt(
		pow(random.x - x, 2) +
		pow(random.y - y, 2));
	nx = (random.x - x) / distance;
	ny = (random.y - y) / distance;
	x += nx * vx * dt;
	y += ny * vy * dt;;
	if (sqrt(pow(x - random.x, 2) + pow(y - random.y, 2)) >= distance)
	{
		vx = 0.17;
		vy = 0.17;
		chaseTime = PHANTOM_BAT_CHASE_TIME;

		isFlyToSimonPos = true;
		isFlyToRandomPos = true;
		x = random.x;
		y = random.y;

	}
	this->SetPosition(x, y);
	SetState(PHANTOM_BAT_STATE_FLYING);
}
