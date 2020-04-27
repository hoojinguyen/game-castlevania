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

	//float oldVy;

	float xBackup, yBackup;
	MorningStar* morningStar;

	float xStair, yStair;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_SETTINGS(string line);

	Simon();

public:

	static Simon* GetInstance();

	bool isAttacking;
	bool isSitting;
	bool isJumping;

	bool isRunning;
	bool isGround;

	int untouchable;

	bool isOnStair;
	bool isUpStair;
	bool isDownStair;
	bool canClimbUpStair;
	bool canClimbDownStair;
	int directionStair;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void SetPosition(float x, float y);

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

	void ResetBackupSimon();
	void ResetAnimationAttacking();
	void Reset();

	void Load(LPCWSTR simonFile);

};

