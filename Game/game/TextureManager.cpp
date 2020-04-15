#include "TextureManager.h"

TextureManager* TextureManager::__Instance = NULL;

TextureManager* TextureManager::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new TextureManager();
	return __Instance;
}

void TextureManager::AddTexture(eType type, GTexture* texture)
{
	_ArrTextures[type] = texture;
}

GTexture* TextureManager::GetTexture(eType type)
{
	return _ArrTextures[type];
}

void TextureManager::LoadResource()
{
	// Map
	AddTexture(eType::MAP1, new GTexture("Resources/map/tileset_map1.png", 8, 4, 32));

	// Ground
	AddTexture(eType::TEX_BRICK_MODEL_1, new GTexture("Resources/ground/2.png")); // loại dành cho state 1
	AddTexture(eType::TEX_BRICK_MODEL_2, new GTexture("Resources/ground/2-2.png")); // dành cho state 2
	AddTexture(eType::TEX_BRICK_MODEL_3, new GTexture("Resources/ground/8.png")); // loại nhỏ
	AddTexture(eType::TEX_BRICK_TRANSPARENT, new GTexture("Resources/ground/brick_transparent.png")); // loại trong suốt
	AddTexture(eType::TEX_BRICK_MODEL_3_3_32, new GTexture("Resources/ground/8-2.png")); // loại nhỏ 4 ô
	AddTexture(eType::TEX_BRICK_MODEL_3_4_32, new GTexture("Resources/ground/8-1.png")); // loại nhỏ 4 ô

	AddTexture(eType::TORCH, new GTexture("Resources/ground/0.png", 2, 1, 2));

	// Item
	AddTexture(eType::LARGEHEART, new GTexture("Resources/item/1.png"));
	AddTexture(eType::UPGRADEMORNINGSTAR, new GTexture("Resources/item/3.png"));

	// Weapon
	AddTexture(eType::MORNINGSTAR, new GTexture("Resources/weapon/morningstar.png", 4, 3, 12));

	// Player
	AddTexture(eType::SIMON, new GTexture("Resources/simon.png", 8, 3, 24));

	// Box
	AddTexture(eType::RENDERBBOX, new GTexture("Resources/bbox.png")); // dùng để vẽ BBOX
}

TextureManager::TextureManager()
{
	LoadResource();
}


TextureManager::~TextureManager()
{
	SAFE_DELETE(__Instance);
}
