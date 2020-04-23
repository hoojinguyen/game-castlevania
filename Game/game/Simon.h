#pragma once
#include "MorningStar.h"
#include "GameObject.h"

class Simon : public CGameObject
{
	static Simon* __instance;
	int level;
	int hp;
	int score;
	int life;
	int energy;
	DWORD untouchable_start;
	DWORD timeAttackStart;

	float checkPointX, checkPointY;
	MorningStar* morningStar;

public:
	Simon(float x, float y);
	static Simon* GetInstance();

	bool isAttacking;
	bool isSitting;
	bool isJumping;
	bool isUpStair;
	bool isDownStair;

	bool isRunning;
	bool isGround;

	int untouchable;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	int GetHP() { return this->hp; }
	void SetHP(int hp) { this->hp = hp; }

	void SetState(int state);
	void SetLevel(int l) { level = l; }

	int GetEnergy() { return energy; }
	void SetEnergy(int e) { energy = e; }

	int GetLevelMorningStar();
	void SetAnimationSetMorningStar(LPANIMATION_SET ani_set);

	int GetLife() { return life; }
	void SetLife(int l) { life = l;  }

	int GetScore() { return score; }
	void SetScore(int sco) { score += sco;  }

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void ResetCheckpoint();
	void ResetAnimationAttacking();
	void Reset();

};

