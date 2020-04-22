#include "Simon.h"

Simon::Simon(Camera* camera, vector<Item*>* listItem)
{
	texture = TextureManager::GetInstance()->GetTexture(eType::SIMON);
	sprite = new GSprite(texture, 250);

	type = eType::SIMON;

	this->camera = camera;
	mapWeapon[eType::MORNINGSTAR] = new MorningStar();

	this->listItem = listItem;

	Init();
}

Simon::~Simon()
{
	// SAFE_DELETE(_sprite_deadth);
}

Item* Simon::GetNewItem(int Id, eType Type, float X, float Y)
{
	if (Type == eType::TORCH)
	{
		if (Id == 1 || Id == 4)
			return new LargeHeart(X, Y);

		if (Id == 2 || Id == 3)
			return new UpgradeMorningStar(X, Y);

		return new LargeHeart(X, Y);

	}
}

void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x + 15;
	top = y - 1; // không chỉnh lại y bởi vì hàm Sit() đã điều chỉnh
	right = x + SIMON_BBOX_WIDTH - 15;

	if (isSitting) // simon đang ngồi
	{
		bottom = y + SIMON_BBOX_SITTING_HEIGHT;
	}
	else
	{ 
		bottom = y + SIMON_BBOX_HEIGHT;
	}
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{ 
	/* Không cho lọt khỏi camera */
	if (x < camera->GetBoundaryLeft() - 16)
		x = camera->GetBoundaryLeft() - 16;
	if (x + SIMON_BBOX_WIDTH > camera->GetBoundaryRight() + SCREEN_WIDTH)
		x = (float)(camera->GetBoundaryRight() + SCREEN_WIDTH - SIMON_BBOX_WIDTH);
	/* Không cho lọt khỏi camera */


	/* Update về sprite */
	int index = sprite->GetCurrentFrame();

	if (isSitting)
	{
		if (isAttacking) // tấn công
		{
			/* Xử lí ani ngồi đánh */
			if (index < SIMON_ANI_SITTING_ATTACKING_BEGIN) // nếu ani chưa đúng
			{
				sprite->SelectFrame(SIMON_ANI_SITTING_ATTACKING_BEGIN); // set lại ani bắt đầu
				sprite->timeAccumulated = dt;
			}
			else
			{
				/* Update ani bình thường */
				sprite->timeAccumulated += dt;

				if (sprite->timeAccumulated >= SIMON_TIME_WAIT_ANI_ATTACKING)
				{
					sprite->timeAccumulated -= SIMON_TIME_WAIT_ANI_ATTACKING;
					sprite->SelectFrame(index + 1);
				}
				/* Update ani bình thường */

				if (index > SIMON_ANI_SITTING_ATTACKING_END) // đã đi vượt qua frame cuối
				{
					isAttacking = 0;
					sprite->SelectFrame(SIMON_ANI_SITTING);
				}
			} 
		}
		else
			sprite->SelectFrame(SIMON_ANI_SITTING);
	}
	else
		if (isAttacking)
		{
			/* Xử lí ani đứng đánh */
			if (index < SIMON_ANI_STANDING_ATTACKING_BEGIN) // nếu ani chưa đúng
			{
				sprite->SelectFrame(SIMON_ANI_STANDING_ATTACKING_BEGIN); // set lại ani bắt đầu
				sprite->timeAccumulated = dt;
			}
			else
			{
				/* Update ani bình thường */
				sprite->timeAccumulated += dt;
				if (sprite->timeAccumulated >= SIMON_TIME_WAIT_ANI_ATTACKING)
				{
					sprite->timeAccumulated -= SIMON_TIME_WAIT_ANI_ATTACKING;
					sprite->SelectFrame(index + 1);
				}
				/* Update ani bình thường */
				if (index > SIMON_ANI_STANDING_ATTACKING_END) // đã đi vượt qua frame cuối
				{
					isAttacking = 0;
					sprite->SelectFrame(SIMON_ANI_IDLE);
				}
			}
		}
		else
			if (isWalking) // đang di chuyển
			{
				if (isJumping) // Đang nhảy
				{
					sprite->SelectFrame(SIMON_ANI_JUMPING);
				}
				else
				{
					if (index < SIMON_ANI_WALKING_BEGIN || index >= SIMON_ANI_WALKING_END)
						sprite->SelectFrame(SIMON_ANI_WALKING_BEGIN);
					//cập nhật frame mới
					sprite->Update(dt); // dt này được cập nhật khi gọi update; 
				}
			
			}
			else
				if (isJumping) // nếu ko đi mà chỉ nhảy
				{
					sprite->SelectFrame(SIMON_ANI_JUMPING);
				}
				else
				{
					sprite->SelectFrame(SIMON_ANI_IDLE);		// SIMON đứng yên
				}
	 
	/* Update về sprite */

	GameObject::Update(dt);   
	vy += SIMON_GRAVITY * dt;// Simple fall down

	// check Collision and update x, y for simon
	CollisionWithBrick(coObjects);

	// Check Collision with object hidden and update x, y for simon
	CollisionSimonWithObjectHidden(coObjects);

	// xu ly va cham giua simon va cac item
	CollisionSimonWithItem();


	for (auto& objWeapon : mapWeapon)
	{
		if (objWeapon.second->GetFinish() == false) // vũ khi này chưa kết thúc thì update
		{
			if (objWeapon.second->GetType() == eType::MORNINGSTAR)
			{
				objWeapon.second->SetPosition(this->x, this->y);
				objWeapon.second->SetSpeed(vx, vy); // set vận tốc để kt va chạm
				objWeapon.second->UpdatePositionFitSimon();
			}

			objWeapon.second->Update(dt, coObjects);

			// objWeapon.second->CollisionWithObject(dt, coObjects);

			// xu li va cham giua roi voi ngon duoc
			for (UINT i = 0; i < coObjects->size(); i++)
			{
				if (objWeapon.second->GetLastTimeAttack() > coObjects->at(i)->GetLastTimeAttacked()) // Nếu chưa xét va chạm của lượt attack này ở các frame trước
				{
					bool check = objWeapon.second->isCollision(coObjects->at(i));
					if (check == true) // nếu có va chạm
					{
						GameObject* gameObj = coObjects->at(i);
						gameObj->SubHealth(1);
						listItem->push_back(GetNewItem(gameObj->GetId(), gameObj->GetType(), gameObj->GetX() + 5, gameObj->GetY()));// hiệu ứng hit
					}
				}

			}
		}
	}


}

bool Simon::isCollisionWithItem(Item* objItem)
{
	if (objItem->GetFinish() == true)
		return false;

	float l, t, r, b;
	float l1, t1, r1, b1;
	this->GetBoundingBox(l, t, r, b);  // lấy BBOX của simon

	objItem->GetBoundingBox(l1, t1, r1, b1);
	bool checkAABB = Game::GetInstance()->CheckAABB(l, t, r, b, l1, t1, r1, b1);
	if (checkAABB)
	{
		return true; // check with AABB
	}

	return isCollitionObjectWithObject(objItem);
}


void Simon::CollisionWithBrick(const vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> list_Brick;
	list_Brick.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == eType::BRICK)
			list_Brick.push_back(coObjects->at(i));

	CalcPotentialCollisions(&list_Brick, coEvents); // Lấy danh sách các va chạm

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		// isCollisionAxisYWithBrick = false; // đang ko va chạm trục y
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		// nếu ko va chạm thì min_tx,min_ty = 1.0, còn nếu có thì nó trả về thời gian va chạm. 
		// Còn nx,ny là hướng va chạm,  = 0 nếu ko va chạm;

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		if (ny == -1)
			y += min_ty * dy + ny * 0.4f;   // ny = -1 thì hướng từ trên xuống....
		else
			y += dy;

		if (ny == -1)
		{
			vy = 0.1f;
			dy = vy * dt;

			if (isJumping)
			{
				isJumping = false;
				y = y - PULL_UP_SIMON_AFTER_JUMPING;
			}
		}

		if (ny != 0)
		{
			//isCollisionAxisYWithBrick = true;
			DebugOut(L"%d : Col y = true - dt=%d - y = %f - dy = %f\n", GetTickCount(), dt, y, dy);
		}
		else
		{
			DebugOut(L"%d : Col y = false - dt=%d\n", GetTickCount(), dt);
			//isCollisionAxisYWithBrick = false;// đang ko va chạm trục y
		}

		if (nx != 0 || ny != 0)
		{
			// isHurting = 0;
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void Simon::CollisionSimonWithItem()
{
	for (UINT i = 0; i < listItem->size(); i++)
	{
		// listItem->at(i)->GetFinish() == false && 
		if (listItem->at(i)->isWaitingDisplay() == false) // chưa kết thúc và "không phải" đang chờ để hiển thị
		{
			if (isCollisionWithItem(listItem->at(i)) == true) // có va chạm
			{
					if (listItem->at(i)->GetType() == eType::LARGEHEART) {
						//SetHeartCollect(simon->GetHeartCollect() + 5);
						listItem->at(i)->SetFinish(true);
					}
					if (listItem->at(i)->GetType() == eType::UPGRADEMORNINGSTAR) {
						MorningStar* objMorningStar = dynamic_cast<MorningStar*>(mapWeapon[eType::MORNINGSTAR]);
						objMorningStar->UpgradeLevel(); // Nâng cấp vũ khí roi
						listItem->at(i)->SetFinish(true);
					}
			}

		}

	}

}

void Simon::CollisionSimonWithObjectHidden(const vector<LPGAMEOBJECT>* coObjects)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->GetType() == eType::OBJECT_HIDDEN)
		{
			GameObject* gameObject = coObjects->at(i);
			if (gameObject->GetHealth() > 0)
			{
				if (isCollitionObjectWithObject(gameObject)) // có va chạm xảy ra
				{
					// Dung de chuyen Scene
					SetPosition(SIMON_POSITION_DEFAULT);
				}
			}
		}
	}
}


void Simon::Render(Camera* camera)
{ 
	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);

	D3DXVECTOR2 pos = camera->Transform(x, y);

	int alpha = 255;
 
	if (direction == -1)
		sprite->Draw(pos.x, pos.y, alpha);
	else
		sprite->DrawFlipX(pos.x, pos.y, alpha);


	for (auto& objWeapon : mapWeapon)
	{
		if (objWeapon.second->GetFinish() == false) // vũ khi này chưa kết thúc thì render
		{
			objWeapon.second->Render(camera); // không cần xét hướng, vì Draw của lớp Weapon đã xét khi vẽ
		}
	}
	 
} 
 
void Simon::Init()
{
	Health = SIMON_DEFAULT_HEALTH; // simon dính 16 phát là chết

	Reset();
}

void Simon::Reset()
{
	direction = 1;

	isSitting = 0;
	isJumping = 0;
	isWalking = 0;
	isAttacking = 0;

	vx = 0;
	vy = 0;
}

void Simon::Left()
{
	direction = -1; // quay qua trái
}

void Simon::Right()
{
	direction = 1; // quay qua phải
}

void Simon::Go()
{
	if (isAttacking)
		return;

	vx = SIMON_WALKING_SPEED * direction;
	isWalking = 1;
}

void Simon::Sit()
{
	vx = 0;
	isWalking = 0;

	if (!isSitting) // nếu trước đó simon chưa ngồi
		y = y + PULL_UP_SIMON_AFTER_SITTING; // kéo simon xuống

	isSitting = 1;
}

void Simon::Jump()
{
	if (isJumping || isSitting || isAttacking)
		return;

	vy -= SIMON_VJUMP;
	isJumping = 1;
}

void Simon::Stop()
{
	if (isAttacking)
		return;

	vx = 0;

	isWalking = 0;
	if (isSitting)	// nếu simon đang ngồi
	{
		isSitting = 0; // hủy trạng thái ngồi
		y = y - PULL_UP_SIMON_AFTER_SITTING; // kéo simon lên
	}
	
}

void Simon::SetPositionBackup(float X, float Y)
{
	PositionBackup = D3DXVECTOR2(X, Y);
}

void Simon::Attack(eType typeWeapon)
{ 
	/* Kiểm tra còn đủ HeartCollect ko? */
	switch (typeWeapon)
	{
	case MORNINGSTAR:
	{
		if (isAttacking)
		{
			return;
		}
		break;
	}

	default: // các vũ khí còn lại
	{
		break;
	}
	}

	isAttacking = true; // set trang thái tấn công
	sprite->SelectFrame(0);
	sprite->ResetTime();

	mapWeapon[typeWeapon]->Attack(this->x, this->y, this->direction); // set vị trí weapon theo simon

}

void Simon::SetHeartCollect(int h)
{
	HeartCollect = h;
}

int Simon::GetHeartCollect()
{
	return HeartCollect;
}

int Simon::GetLives()
{
	return Lives;
}

void Simon::SetLives(int l)
{
	Lives = l;
}

int Simon::GetScore()
{
	return score;
}

void Simon::SetScore(int s)
{
	score = s;
}


