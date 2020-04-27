#include "GameObject.h"

class MorningStar : public CGameObject
{
private:
	CAnimation* ani;

	int indexAni;
	int damage;
	int level;

public:
	MorningStar();
	~MorningStar();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Render(bool isRight);
	void Render();

	void SetPosition(float x, float y, bool isSitting);

	void SetLevel(int level) { this->level = level; }
	int GetLevel() { return this->level; }

	int GetCurrentFrame();

	void ResetAnimation();

};
