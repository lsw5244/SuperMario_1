#pragma once
#include "Config.h"
#include "GameEntity.h"

class EnemyTankManager;
class EnemyTankFactory;
class AmmoManager;
class PlayerTank;
class Image;
class StageManager : public GameEntity
{
private:
	AmmoManager* ammoManager;
	PlayerTank* playerTank;
	EnemyTankManager* enemyTankManager;
	EnemyTankFactory* enemyTankFactory[4];
	enum class EnemyTankSpawnInfo {
		NormalTankSpawm,
		FastTankSpawm,
		ShootTankSpawm,
		BigTankSpawm
	};

	TILE_INFO(*tileInfo)[TILE_COUNT];
	POINTFLOAT pos;
	EnemyTankSpawnInfo enemyTankSpawnInfo[10][20];
	int stageNum;
	int spawnNum;
	int spawnPos;
	float spawnDelay;
	bool spawnCheck;

	Image* enemySpawnEffect;
	bool spawnEffectCheck;
	bool spawnEffectUpDown;
	float spawnEffectTime;
	int spawnEffectFrame;
	int spawnEffectCount;

	Image* gameOver;
	bool gameOverCheck;
	float gameOverTime;
	float gameOverPos;

	bool winCheck;
	bool deadCheck;
public:
	void SetData(EnemyTankManager* enemyTankManager, PlayerTank* playerTank, AmmoManager* ammoManager, TILE_INFO(*tileInfo)[TILE_COUNT]);
	int GetSpawnNum() { return spawnNum; }
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~StageManager() = default;

	void SpawnEffect();
};

