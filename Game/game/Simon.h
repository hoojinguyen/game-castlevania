#pragma once
#include "GameObject.h"
#include "Item.h"

#include "Weapon.h"
#include "MorningStar.h"
#include "Axe.h"
#include "Dagger.h"
#include "Boomerang.h"
#include "FireBomb.h"
#include "Stopwatch.h"

class Simon : public CGameObject
{
	static Simon* __instance;
	int level;
	int hp;
	int score;
	int life;
	int energy;
	int heart;

	float DoCaoDiDuoc = 0;

	DWORD untouchable_start;
	DWORD timeAttackStart;
	DWORD hurtable_start;

	float oldVy;

	float xBackup, yBackup;

	float xStair, yStair;

	int typeWeaponCollect;
	int typeShotCollect;

	bool _IsFirstOnStair;

	Axe* axes[3];
	Dagger* daggers[3];
	Boomerang* boomerangs[3];
	FireBomb* fireBombs[3];
	Stopwatch* stopwatchs[3];
	MorningStar* morningStar;

	void SetTypeOfWeapon(int item);

	Simon();

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_SETTINGS(string line);

public:

	static Simon* GetInstance();

	Weapon* weapons[3];

	bool isAttacking;
	bool isSitting;
	bool isJumping;

	bool isRunning;
	bool isGround;
	bool isWall;

	bool isHurt;

	int hurtable;

	int untouchable;

	bool isOnStair;
	bool isUpStair;
	bool isDownStair;
	bool canClimbUpStair;
	bool canClimbDownStair;
	int directionStair;

	bool isFreeze; // Trạng thái đóng băng thay đổi màu liên tục
	DWORD timeFreezeStart; // thời gian đã đóng băng

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void Load(LPCWSTR simonFile);

	int GetTypeWeaponCollect() { return typeWeaponCollect; }
	int GetTypeShotCollect() { return typeShotCollect; }

	void Hurted(int damage);

	void SetPosition(float x, float y);
	void SetPositionBackup(float xBackup, float yBackup);

	int GetHP() { return this->hp; }
	void SetHP(int hp) { this->hp = hp; }

	void SetState(int state);
	void SetLevel(int l) { level = l; }

	int GetHeart() { return heart; }
	void SetHeart(int h) { heart = h; }

	int GetLevelMorningStar();
	void SetAnimationSetMorningStar(LPANIMATION_SET ani_set);

	int GetLife() { return life; }
	void SetLife(int l) { life = l;  }

	int GetScore() { return score; }
	void SetScore(int sco) { score += sco;  }

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartHurting() { isHurt = true; hurtable = 1; hurtable_start = GetTickCount(); }

	void ResetBackupSimon();
	void ResetAnimationAttacking();
	void ResetAnimationHurt();
	void Reset();

	void HandleCollisionSimonWithItem(Item* item, DWORD dt);

};

