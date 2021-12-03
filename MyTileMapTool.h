#pragma once
#include "GameEntity.h"
#include "Config.h"



class Image;
class MyTileMapTool : public GameEntity
{
private:
	TILE map[MAP_HEIGHT][MAP_WIDTH] = {};

	Image* mapSpriteImg = ImageManager::GetSingleton()->FindImage("Image/mario_overwordTile_real.bmp");
	SampleTile sampleTileInfo[TILE_SPRITE_HEIGHT][TILE_SPRITE_WIDTH] = {};
	SampleTile selectTile = {};

	int page = 0;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void Save(int saveIndex = 0);
	void Load(int loadIndex = 0);
};

