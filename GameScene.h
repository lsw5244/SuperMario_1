#pragma once
#include "GameEntity.h"
#include "Gunba.h"
#include "PlayerCharacter.h"
#include "MacroCollection.h"
#include "StructCollection.h"
#include "FireAmmo.h"
#include "AmmoManager.h"
#include "ItemManager.h"

class Image;
class GameScene : public GameEntity
{
private:
	PlayerCharacter* mario;
	Gunba mushroom;
	TILE map[MAP_HEIGHT][MAP_WIDTH] = {};
	Image* mapSpriteImg = {};

	ItemManager itemManager;
	//int globalPos = 0;
	AmmoManager ammoManger;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~GameScene() = default;

	void Load(int loadIndex = 0);

};

