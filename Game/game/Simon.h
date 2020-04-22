#ifndef __SIMON_H__
#define __SIMON_H__

#include "GameObject.h"
#include "Weapon.h"
#include "MorningStar.h"
#include "Item.h" 

#include "LargeHeart.h"
#include "UpgradeMorningStar.h"

#define SIMON_POSITION_DEFAULT  50.0f, 0

#define SIMON_BBOX_WIDTH 60
#define SIMON_BBOX_HEIGHT 63
#define SIMON_BBOX_SITTING_HEIGHT 45
#define SIMON_BBOX_JUMPING_HEIGHT 45

#define SIMON_GRAVITY 0.005f
#define SIMON_GRAVITY_JUMPING 0.001f 

#define SIMON_VJUMP 0.8f

#define PULL_UP_SIMON_AFTER_JUMPING 18.0f // Kéo simon lên 18px sau khi nhảy, tránh overlaping do BBOX bottom thu lại khi nhảy
#define PULL_UP_SIMON_AFTER_SITTING 18.0f // Kéo simon lên 18px sau khi ngồi rồi đứng dậy, tránh overlaping do BBOX bottom thu lại khi ngồi

#define SIMON_WALKING_SPEED 0.12f 

#define SIMON_STATE_IDLE 0
#define SIMON_STATE_WALKING 1

/* Ani đang đi*/
#define SIMON_ANI_WALKING_BEGIN 1
#define SIMON_ANI_WALKING_END 3

#define SIMON_ANI_IDLE 0

#define SIMON_ANI_JUMPING 4

#define SIMON_ANI_SITTING 4

/*Ani đang ngồi đánh*/
#define SIMON_ANI_SITTING_ATTACKING_BEGIN 15
#define SIMON_ANI_SITTING_ATTACKING_END 17

/*Ani đang đứng đánh*/
#define SIMON_ANI_STANDING_ATTACKING_BEGIN 5
#define SIMON_ANI_STANDING_ATTACKING_END 7

#define SIMON_DEFAULT_HEALTH 16

/* Time Ani attack */
#define SIMON_TIME_WAIT_ANI_ATTACKING 120// thời gian  của mỗi frame khi tấn công

class Simon : public GameObject
{
private:
	int HeartCollect; // số lượng item heart người chơi nhặt được
	int Lives; // số mạng của simon
	int score; // điểm

	bool isWalking_Backup;
	bool isJumping_Backup;
	bool isSitting_Backup;
	bool isAttacking_Backup;
	int directionY_Backup;
	int directionAfterGo;

	D3DXVECTOR2 PositionBackup;

	Camera* camera;

	vector<Item*>* listItem;

public:
	
	bool isWalking;
	bool isJumping;
	bool isSitting;
	bool isAttacking;

	bool isCollisionAxisYWithBrick = false; // Đang va chạm với đất theo trục y

public:
	Simon(Camera* camera, vector<Item*>* listItem);
	~Simon();

	unordered_map<eType, Weapon*> mapWeapon;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);
	 
	void Left();  // set lại hướng của simon
	void Right(); // set lại hướng của simon
	void Go();
	void Sit();
	void Jump();
	void Stop();

	void Attack(eType typeWeapon);

	void SetHeartCollect(int h);
	int GetHeartCollect();
	int GetLives();
	void SetLives(int l);
	int GetScore();
	void SetScore(int s);

	void SetPositionBackup(float X, float Y);  // lưu vị trí cần backup để simon die thì bắt đầu lại từ đây 

	bool isCollisionWithItem(Item* objItem);

	void CollisionWithBrick(const vector<LPGAMEOBJECT>* coObjects = NULL);

	void CollisionSimonWithItem();

	void CollisionSimonWithObjectHidden(const vector<LPGAMEOBJECT>* coObjects = NULL);

	static Item* GetNewItem(int Id, eType Type, float X, float Y);


	void Init(); // khởi tạo các trạng thái, HeartCollect, Heath, Lives, Score
	void Reset(); // khởi tạo lại các trạng thái.
};

#endif