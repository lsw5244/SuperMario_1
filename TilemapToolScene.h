#pragma once
#include "Config.h"
#include "GameEntity.h"

#define POS 8
typedef struct tagSampleTile
{
	RECT rc;
	int frameX, frameY;
	int width, height;
} SAMPLE_TILE_INFO;

class Image;
class TilemapToolScene : public GameEntity
{
private:
	HPEN pen, oPen;

	SAMPLE_TILE_INFO sampleTileInfo[SAMPLE_TILE_COUNT][SAMPLE_TILE_COUNT];
	TILE_INFO tileInfo[TILE_COUNT][TILE_COUNT];
	Image* sampleImage;
	Image* bin;
	SAMPLE_TILE_INFO selectedSampleTile;

	bool check;
	bool mouseCheck;
	POINT mousePos[2];
	POINTFLOAT view;
	POINT mouse;

	void SetTerrain(TILE_INFO* tileInfo, int x, int y);

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~TilemapToolScene() = default;
	void Save();
	void Load();

};

