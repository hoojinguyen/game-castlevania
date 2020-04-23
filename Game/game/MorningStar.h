#include "GameObject.h"

class MorningStar : public CGameObject
{
private:
	int indexAni;
	CAnimation* ani;
	int damage;
	int level;
public:
	MorningStar();
	~MorningStar();

	void Render();
	void Render(bool IsRight);
	void SetPosition(float x, float y, bool isSitting);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void ResetAnimation();
	int GetCurrentFrame();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetLevel(int level) { this->level = level; }
	int GetLevel() { return this->level; }
};
