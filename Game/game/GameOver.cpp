#include "GameOver.h"
#include "Define.h"
#include "Game.h"

int GameOver::selected = GAMEOVER_SELECT_CONTINUE;

GameOver::GameOver()
{
	this->d3ddv = CGame::GetInstance()->GetDirect3DDevice();
	this->spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	font = NULL;

	D3DXFONT_DESC FontDesc = {
		12,
		7,
		5,
		5,
		false,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY,
		FF_DONTCARE, L"font\\prstart.ttf" };


	D3DXCreateFontIndirect(d3ddv, &FontDesc, &font);

	SetRect(&rectLineTitle, 90, 70, SCREEN_WIDTH, 85);
	SetRect(&rectLineScore, 80, 90, SCREEN_WIDTH, 105);
	SetRect(&rectLineOne, 100, 110, SCREEN_WIDTH, 125);
	SetRect(&rectLineTwo, 100, 130, SCREEN_WIDTH, 145);
	lineTitle = L"GAME OVER\n";
	lineOne = L"Countrinue\n";
	lineTwo = L"End game";


	CSprites* sprites = CSprites::GetInstance();
	sprite = sprites->Get(40002);
}

GameOver::~GameOver()
{
}


void GameOver::Render(int score)
{
	if (this->selected == GAMEOVER_SELECT_CONTINUE) {

		sprite->DrawWithoutCamera(80, 110);
	}
	else {
		sprite->DrawWithoutCamera(80, 130);
	}

	lineScore = L"YOUR SCORE: " + to_wstring(score) + L"\n";

	font->DrawText(spriteHandler, lineTitle.c_str(), -1, &rectLineTitle, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
	font->DrawText(spriteHandler, lineScore.c_str(), -1, &rectLineScore, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
	font->DrawText(spriteHandler, lineOne.c_str(), -1, &rectLineOne, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
	font->DrawText(spriteHandler, lineTwo.c_str(), -1, &rectLineTwo, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));

}
