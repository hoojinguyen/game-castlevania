#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"
#include "Animations.h"


using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;

	float dx, dy;		// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};


class CGameObject
{
public:

	float x;
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;

	int state;

	DWORD dt;

	LPANIMATION_SET animation_set;

	int id;
	bool isEnable;
	bool isDeadth;
	int width;
	int height;

	int type;
	int typeItem;

	bool enableBoundingBox = false;

	void SetEnableBoundingBox(bool e) { enableBoundingBox = e; }
	bool GetEnableBoundingBox() { return enableBoundingBox; }

public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }

	int GetState() { return this->state; }

	void RenderBoundingBox();

	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }
	void SetAnimationSet(int ani_set_id);


	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny,
		float& rdx,
		float& rdy);

	CGameObject();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }

	void SetID(int ID) { id = ID; }
	int GetID() { return id; }

	void SetWidth(int w) { width = w; }
	void SetHeight(int h) { height = h; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }

	void SetEnable(bool e) { if (e) { isDeadth = false; } isEnable = e; }
	bool GetEnable() { return isEnable; }

	

	void SetDeadth(bool dead) { isDeadth = dead; }
	bool GetDeadth() { return isDeadth; }

	void ResetAni(int aniID) { animation_set->at(aniID)->Reset(); }

	void SetType(int t) { type = t; }
	int GetType() { return type; }

	void SetTypeItem(int typeItem) { this->typeItem = typeItem; }
	int GetTypeItem() { return this->typeItem; }

	~CGameObject();
};

