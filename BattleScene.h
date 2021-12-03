#pragma once
#include "GameEntity.h"
#include "Config.h"

class Tank;
class Image;
class PlayerTank;
class EnemyTanks;
class EnemyTankFactory;
class AmmoManager;
class ItemManager;
class EnemyTankManager;
class UIManager;
class StageManager;
class BattleScene : public GameEntity
{
private:
	// 플레이어 로켓
	Tank* enemyTank;
	PlayerTank* playerTank;

	// 타일 샘플정보
	Image* sampleImage;
	// 배틀 백그라운드
	Image* battleBackGround;
	// 배경 이미지
	Image* backGround;

	Image* grayBackGround1;
	Image* grayBackGround2;
	Image* stageNumImage;
	Image* stage;
	bool entryScene1;
	bool entryScene2;
	bool stageRender;
	float stageTime;
	float grayPosY1;
	float grayPosY2;

	bool waterCheck;
	float waterTime;

	ItemManager* itemManager;

	StageManager* stageManager;
	EnemyTankManager* enemyTankManager;

	TILE_INFO tileInfo[TILE_COUNT][TILE_COUNT];
	TILE_INFO bufferTileInfo[TILE_COUNT][TILE_COUNT];

	HPEN pen, oPen;

	AmmoManager* ammoManager;

	UIManager* uIManager;

	int stageNum;
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;	// 오버로딩
	virtual void Release() override;
	virtual ~BattleScene() = default;
	int Load(int num);
};

