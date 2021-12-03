#pragma once
#include "GameEntity.h"
#include "Config.h"

#define MAP_WIDTH 40//211
#define MAP_HEIGHT 15

#define TILE_SPRITE_WIDTH 11
#define TILE_SPRITE_HEIGHT 13

#define TILE_SIZE 16		// 가로 세로 16픽셀

class Image;
enum class BlockType
{
	CantDestroyBlock, CanDestroyBlock, ItemBlock, Coin, Flag, BackGround, CastleDoor
};

struct SampleTile
{
	RECT rc;
	int frameX;
	int frameY;
};

struct TILE
{
	BlockType type;
	RECT rc;
	int frameX;
	int frameY;
 };

class MyTileMapTool : public GameEntity
{
private:
	TILE map[MAP_HEIGHT][MAP_WIDTH] = {};

	Image* mapSpriteImg = ImageManager::GetSingleton()->FindImage("Image/mario_overwordTile_real.bmp");
	SampleTile sampleTileInfo[TILE_SPRITE_HEIGHT][TILE_SPRITE_WIDTH] = {};
	SampleTile selectTile = {};


public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void Save(int saveIndex = 0);
	void Load(int loadIndex = 0);
};

