#pragma once
#include "GameEntity.h"
#include "Config.h"

class Image;
class MyTileMapTool : public GameEntity
{
private:
	TILE map[MAP_HEIGHT][MAP_WIDTH]									 = {};
	TILE selectTile													 = {};
	SampleTile sampleTileInfo[TILE_SPRITE_HEIGHT][TILE_SPRITE_WIDTH] = {};

	Image* mapSpriteImg	= {};

	const int MAX_PAGE	= 4;
	int page			= 0;

	void InputTileInfo(int r, int c);

	void SelectTileInfoSet(int frameX, int frameY);
	void TileInfoSetting(TILE& tile, BlockType type, int frameX, int frameY, int animationFrameX, int maxAnimationFrameX, int itemCount, bool isCollider);

public:
	virtual HRESULT Init()		 override;
	virtual void Update()		 override;
	virtual void Render(HDC hdc) override;
	virtual void Release()		 override;

	void Save(int saveIndex = 0);
	void Load(int loadIndex = 0);
};

