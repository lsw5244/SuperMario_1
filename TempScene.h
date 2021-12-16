#pragma once
#include "GameEntity.h"
#include "Gunba.h"
#include "PlayerCharacter.h"
#include "MacroCollection.h"
#include "StructCollection.h"
#include "FireAmmo.h"

class Image;
class TempScene : public GameEntity
{
private:
	PlayerCharacter mario;
	Gunba mushroom;
	TILE map[MAP_HEIGHT][MAP_WIDTH] = {};
	Image* mapSpriteImg = {};

	//int globalPos = 0;
	FireAmmo ammo;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~TempScene() = default;

	void Load(int loadIndex = 0);

};

