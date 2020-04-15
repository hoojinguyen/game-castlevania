﻿#pragma once
#include "define.h"
#include "GSprite.h"
#include "GTexture.h"
#include "Camera.h"
#include "DebugRenderBBOX.h"
#include "define.h"
#include "TextureManager.h"

using namespace std;

class GameObject; 
typedef GameObject * LPGAMEOBJECT;

struct CollisionEvent;
typedef CollisionEvent * LPCOLLISIONEVENT;

struct CollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};

class GameObject
{
protected:
	DWORD LastTimeAttacked; // thời điểm bị tấn công cuối cùng

	int Health;
	int id; // ID của object

	int direction;	// hướng -1 : trái, 1: phải
	eType type; // Loại Object

	float x;
	float y;

	float dx;
	float dy;

	float vx;
	float vy;

	DWORD dt;

	GTexture* texture;
	GSprite* sprite;

public:
 
	GameObject();
	virtual ~GameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera) = 0;

	void RenderBoundingBox(Camera* camera);
	LPCOLLISIONEVENT SweptAABBEx(GameObject* coO);
	void CalcPotentialCollisions(vector<GameObject*>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny);

	bool isCollitionObjectWithObject(GameObject* obj); 	// kiểm tra bằng AABB và Sweept AABB
	bool CheckAABB(GameObject* obj);

	void SubHealth(int th);
	int GetHealth();
	void SetHealth(int h);
	void SetDirection(int d);
	int GetDirection();
	void SetId(int ID);
	int GetId();
	  
	void GetPosition(float& x, float& y);
	void SetPosition(float x, float y);
	void GetSpeed(float& vx, float& vy);
	void SetSpeed(float vx, float vy);

	float GetX();
	void SetX(float X);
	float GetY();
	void SetY(float Y);
	float GetVx();
	void SetVx(float VX);
	float GetVy();
	void SetVy(float VY);
	int GetHeight();
	int GetWidth();
	eType GetType();

	DWORD GetLastTimeAttacked();
	void SetLastTimeAttacked(DWORD t);

	void SetTexture(GTexture* tex);
	GSprite* GetSprite();

};