#include "Enemy.h"
#include "define.h"

int Enemy::score = 0;
float Enemy::stopTime = 0;
int Enemy::timestop = 0;
DWORD Enemy::timestop_start = 0;
bool Enemy::isStop = false;

Enemy::Enemy()
{
	collisionEffect = new CollisionEffect();
	deadEffect = new DeadEffect();
	isEnable = true;
	isDeadth = false;
	isBoss = false;
}

Enemy::Enemy(int hp)
{
	collisionEffect = new CollisionEffect();
	deadEffect = new DeadEffect();

	this->respawnTime = 0;
	this->hp = hp;
	hpC = hp;
	e_prevHP = hp;
	isEnable = true;
	isDeadth = false;
}

Enemy::~Enemy()
{
}

void Enemy::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (!isStop)
	{
		CGameObject::Update(dt, coObjects);
	}

	if (!isDeadth)
	{
		if (isEnable)
		{
			respawnTime = 0;
			if (hp < e_prevHP)
			{
				e_prevHP = hp;
			}

			if (hp <= 0)
			{
				isDeadth = true;
				isEnable = false;
				respawnTime = GetTickCount();
				GetDeadEffect()->SetEnable(true);
				AddScore();
				return;
			}
			if (isStop == true)
			{
				DWORD now = GetTickCount();
				if (now - timestop_start > TIME_STOP_ENEMIES)
				{
					isStop = false;
					timestop = 0;
					timestop_start = 0;
				}
			}
			collisionEffect->SetPosition(x, y + 10);
			deadEffect->SetPosition(x + 3, y - 3);
		}
	}

	if (!isEnable)
	{
		//respawnTime += dt;
	}

	collisionEffect->Update(dt);
	deadEffect->Update(dt);
}

void Enemy::Render()
{
	collisionEffect->Render();
	deadEffect->Render();
}

void Enemy::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
}

void Enemy::Reload()
{
	isEnable = false;
	isDeadth = true;
	hp = hpC;
	e_prevHP = hp;
	respawnTime = 0;
}

void Enemy::Respawn()
{
	isEnable = true;
	isDeadth = false;
	hp = hpC;
	e_prevHP = hp;
	respawnTime = 0;
	x = xRespawn;
	y = yRespawn;
}

void Enemy::AddScore()
{
	Enemy::score += point;
}

int Enemy::GetScore()
{
	return score;
}

void Enemy::SetScore(int score)
{
	Enemy::score = score;
}