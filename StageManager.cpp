#include "StageManager.h"
#include "EnemyTankManager.h"
#include "EnemyTankFactory.h"
#include "TimerManager.h"
#include "AmmoManager.h"
#include "PlayerTank.h"
#include "Image.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "ScoreManager.h"
#include "GameDataManager.h"

#define NormalTank		enemyTankFactory[0]->CreateEnemyTank()
#define FastTank		enemyTankFactory[1]->CreateEnemyTank()
#define ShootTank		enemyTankFactory[2]->CreateEnemyTank()
#define BigTank			enemyTankFactory[3]->CreateEnemyTank()

void StageManager::SetData(EnemyTankManager* enemyTankManager, PlayerTank* playerTank, AmmoManager* ammoManager, TILE_INFO(*tileInfo)[TILE_COUNT])
{
	this->tileInfo = tileInfo;
	this->ammoManager = ammoManager;
	this->enemyTankManager = enemyTankManager;
	this->playerTank = playerTank;
	stageNum = GameDataManager::GetSingleton()->GetIsStage();
}

HRESULT StageManager::Init()
{
	enemyTankFactory[0] = new NormalTankFactory;
	enemyTankFactory[1] = new FastMoveTankFactory;
	enemyTankFactory[2] = new FastShootTankFactory;
	enemyTankFactory[3] = new BigTankFactory;
	
	enemySpawnEffect = ImageManager::GetSingleton()->FindImage("Image/Effect/Spawn_Effect.bmp");
	spawnEffectCheck = false;
	spawnEffectUpDown = true;;
	spawnEffectTime = 0.0f;
	spawnEffectFrame = 0;
	spawnEffectCount = 0;
	spawnCheck = false;
	
	spawnDelay = 5.0f;
	spawnPos = 0;
	spawnNum = 0;
	pos.x = 16 + (8);
	pos.y = 16;

	gameOver = ImageManager::GetSingleton()->FindImage("Image/Title/BattleGameOver.bmp");
	gameOverCheck = false;
	gameOverTime = 0.0f;
	gameOverPos = WIN_SIZE_Y + (gameOver->GetHeight() / 2);

	winCheck = true;
	deadCheck = true;

	{
		enemyTankSpawnInfo[0][0] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][1] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][2] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][3] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][4] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][5] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][6] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][7] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][8] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][9] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][10] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][11] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][12] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][13] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][14] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][15] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][16] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][17] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][18] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[0][19] = EnemyTankSpawnInfo::FastTankSpawm;
	}
	// 1스테이지 초기화

	{
		enemyTankSpawnInfo[1][0] = EnemyTankSpawnInfo::BigTankSpawm;
		enemyTankSpawnInfo[1][1] = EnemyTankSpawnInfo::BigTankSpawm;
		enemyTankSpawnInfo[1][2] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[1][3] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[1][4] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[1][5] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[1][6] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][7] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][8] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][9] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][10] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][11] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][12] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][13] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][14] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][15] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][16] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][17] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][18] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][19] = EnemyTankSpawnInfo::NormalTankSpawm;
	}
	// 2스테이지 초기화

	{
		enemyTankSpawnInfo[2][0] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[2][1] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[2][2] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[2][3] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[2][4] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[2][5] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[2][6] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[2][7] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[2][8] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[2][9] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[2][10] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[2][11] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[2][12] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[2][13] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[2][14] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[2][15] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[2][16] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[2][17] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[2][18] = EnemyTankSpawnInfo::BigTankSpawm;
		enemyTankSpawnInfo[2][19] = EnemyTankSpawnInfo::BigTankSpawm;
	}
	// 3스테이지 초기화

	{
		enemyTankSpawnInfo[3][0] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[3][1] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[3][2] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[3][3] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[3][4] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[3][5] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[3][6] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[3][7] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[3][8] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[3][9] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[3][10] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[3][11] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[3][12] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[3][13] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[3][14] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[3][15] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[3][16] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[3][17] = EnemyTankSpawnInfo::BigTankSpawm;
		enemyTankSpawnInfo[3][18] = EnemyTankSpawnInfo::BigTankSpawm;
		enemyTankSpawnInfo[3][19] = EnemyTankSpawnInfo::BigTankSpawm;
	}
	// 4스테이지 초기화

	{
		enemyTankSpawnInfo[4][0] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[4][1] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[4][2] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[4][3] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[4][4] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[4][5] = EnemyTankSpawnInfo::BigTankSpawm;
		enemyTankSpawnInfo[4][6] = EnemyTankSpawnInfo::BigTankSpawm;
		enemyTankSpawnInfo[4][7] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[4][8] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[4][9] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[4][10] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[4][11] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[4][12] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[4][13] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[4][14] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[4][15] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[4][16] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[4][17] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[4][18] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[4][19] = EnemyTankSpawnInfo::FastTankSpawm;
	}
	// 5스테이지 초기화

	{
		enemyTankSpawnInfo[5][0] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[5][1] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[5][2] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[5][3] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[5][4] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[5][5] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[5][6] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[5][7] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[5][8] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[5][9] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[5][10] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[5][11] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[5][12] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[5][13] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[5][14] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[5][15] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[5][16] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[5][17] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[5][18] = EnemyTankSpawnInfo::BigTankSpawm;
		enemyTankSpawnInfo[5][19] = EnemyTankSpawnInfo::BigTankSpawm;
	}
	// 6스테이지 초기화

	{
		enemyTankSpawnInfo[6][0] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[6][1] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[6][2] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[6][3] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[6][4] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[6][5] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[6][6] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[6][7] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[6][8] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[6][9] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[6][10] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[6][11] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[6][12] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[6][13] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[6][14] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[6][15] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[6][16] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[6][17] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[6][18] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[6][19] = EnemyTankSpawnInfo::NormalTankSpawm;
	}
	// 7스테이지 초기화

	{
		enemyTankSpawnInfo[7][0] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[7][1] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[7][2] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[7][3] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[7][4] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[7][5] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[7][6] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[7][7] = EnemyTankSpawnInfo::BigTankSpawm;
		enemyTankSpawnInfo[7][8] = EnemyTankSpawnInfo::BigTankSpawm;
		enemyTankSpawnInfo[7][9] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[7][10] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[7][11] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[7][12] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[7][13] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[7][14] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[7][15] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[7][16] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[7][17] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[7][18] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[7][19] = EnemyTankSpawnInfo::NormalTankSpawm;
	}
	// 8스테이지 초기화

	{
		enemyTankSpawnInfo[8][0] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[8][1] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[8][2] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[8][3] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[8][4] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[8][5] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[8][6] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[8][7] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[8][8] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[8][9] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[8][10] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[8][11] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[8][12] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[8][13] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[8][14] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[8][15] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[8][16] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[8][17] = EnemyTankSpawnInfo::BigTankSpawm;
		enemyTankSpawnInfo[8][18] = EnemyTankSpawnInfo::BigTankSpawm;
		enemyTankSpawnInfo[8][19] = EnemyTankSpawnInfo::BigTankSpawm;
	}
	// 9스테이지 초기화

	{
		enemyTankSpawnInfo[9][0] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[9][1] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[9][2] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[9][3] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[9][4] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[9][5] = EnemyTankSpawnInfo::ShootTankSpawm;
		enemyTankSpawnInfo[9][6] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[9][7] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[9][8] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[9][9] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[9][10] = EnemyTankSpawnInfo::BigTankSpawm;
		enemyTankSpawnInfo[9][11] = EnemyTankSpawnInfo::BigTankSpawm;
		enemyTankSpawnInfo[9][12] = EnemyTankSpawnInfo::BigTankSpawm;
		enemyTankSpawnInfo[9][13] = EnemyTankSpawnInfo::BigTankSpawm;
		enemyTankSpawnInfo[9][14] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[9][15] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[9][16] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[9][17] = EnemyTankSpawnInfo::BigTankSpawm;
		enemyTankSpawnInfo[9][18] = EnemyTankSpawnInfo::BigTankSpawm;
		enemyTankSpawnInfo[9][19] = EnemyTankSpawnInfo::BigTankSpawm;
	}
	// 10스테이지 초기화

	return S_OK;
}

void StageManager::Update()
{
	if(spawnNum < 20)spawnDelay += TimerManager::GetSingleton()->GetDeltaTime();
	if (spawnDelay >= 3.0f && enemyTankManager->GetEnemyTankVecSize() < 4 && !spawnEffectCheck) {
		spawnEffectCheck = true;
		spawnPos++;
		if (spawnPos == 4) spawnPos = 1;
		if (spawnPos == 1) {
			pos.x = 16 + (8);
		}
		else if (spawnPos == 2) {
			pos.x = 16 + (8 + 96);
		}
		else {
			pos.x = 16 + (8 + 192);
		}
	}

	if (spawnEffectCheck)
	{
		spawnEffectTime += TimerManager::GetSingleton()->GetDeltaTime();
		SpawnEffect();
	}
	
	if (spawnCheck) {
		switch (enemyTankSpawnInfo[stageNum-1][spawnNum]) {
		case EnemyTankSpawnInfo::NormalTankSpawm:
			if (spawnNum == 3 || spawnNum == 11 || spawnNum == 17) enemyTankManager->NewEnemyTank(NormalTank, spawnPos, true);
			else enemyTankManager->NewEnemyTank(NormalTank, spawnPos, false);
			break;
		case EnemyTankSpawnInfo::FastTankSpawm:
			if (spawnNum == 3 || spawnNum == 11 || spawnNum == 17) enemyTankManager->NewEnemyTank(FastTank, spawnPos, true);
			else enemyTankManager->NewEnemyTank(FastTank, spawnPos, false);
			break;
		case EnemyTankSpawnInfo::ShootTankSpawm:
			if (spawnNum == 3 || spawnNum == 11 || spawnNum == 17) enemyTankManager->NewEnemyTank(ShootTank, spawnPos, true);
			else enemyTankManager->NewEnemyTank(ShootTank, spawnPos, false);
			break;
		case EnemyTankSpawnInfo::BigTankSpawm:
			if (spawnNum == 3 || spawnNum == 11 || spawnNum == 17) enemyTankManager->NewEnemyTank(BigTank, spawnPos, true);
			else enemyTankManager->NewEnemyTank(BigTank, spawnPos, false);
			break;
		}
		ammoManager->SetVecEnemyTank(enemyTankManager->GetVecEnemyTanks());
		ammoManager->SetTileInfoAndEnemyVec();
		enemyTankManager->SetVecEnemyTank();
		playerTank->SetVecEnemyTank(enemyTankManager->GetVecEnemyTanks());
		spawnNum++;
		spawnDelay = 0;
		spawnCheck = false;
	}


	if (spawnNum >= 20 && enemyTankManager->GetEnemyTankVecSize() == 0 && winCheck
		|| KeyManager::GetSingleton()->IsOnceKeyDown('2')) {
		deadCheck = false;
		for (int y = 0; y < TILE_COUNT; y++) {
			for (int x = 0; x < TILE_COUNT; x++) {
				GameDataManager::GetSingleton()->SetTileInfo(tileInfo[y][x], y, x);
			}
		}
		GameDataManager::GetSingleton()->SetPlayerIsDead(false);
		GameDataManager::GetSingleton()->AddIsStage();
		GameDataManager::GetSingleton()->SetPlayerLevel(playerTank->GetLevel());
		GameDataManager::GetSingleton()->SetPlayerLife(playerTank->GetLife());
		SceneManager::GetSingleton()->ChangeScene("TotalScene");
		return;
	}
	if (playerTank->GetLife() == 0 || tileInfo[25][12].terrain == Terrain::BaseDes && deadCheck) {
		winCheck = false;
		if (gameOverPos > (WIN_SIZE_Y / 2)) {
			gameOverPos -= 70 * TimerManager::GetSingleton()->GetDeltaTime();
		} else {
			gameOverPos = (WIN_SIZE_Y / 2);
			gameOverTime += TimerManager::GetSingleton()->GetDeltaTime();
			if(gameOverTime > 2.0f) gameOverCheck = true;

		}
		if (gameOverCheck) {
			GameDataManager::GetSingleton()->SetPlayerLevel(0);
			GameDataManager::GetSingleton()->SetPlayerLife(2);
			GameDataManager::GetSingleton()->AddIsStage();
			GameDataManager::GetSingleton()->SetPlayerIsDead(true);
			SceneManager::GetSingleton()->ChangeScene("TotalScene");
			return;

		}
	}
}

void StageManager::Render(HDC hdc)
{
	if (spawnEffectCheck)
	{
		enemySpawnEffect->Render(hdc, pos.x, pos.y, spawnEffectFrame, 0);
	}
	gameOver->Render(hdc, (WIN_SIZE_X / 2)-7, gameOverPos);
}

void StageManager::Release()
{
	SAFE_DELETE(enemyTankFactory[0]);
	SAFE_DELETE(enemyTankFactory[1]);
	SAFE_DELETE(enemyTankFactory[2]);
	SAFE_DELETE(enemyTankFactory[3]);
}

void StageManager::SpawnEffect()
{
	if (spawnEffectTime >= 0.05) {
		if (spawnEffectUpDown)spawnEffectFrame++;
		else spawnEffectFrame--;
		if (spawnEffectFrame == 0) spawnEffectUpDown = true;
		if (spawnEffectFrame == 3) spawnEffectUpDown = false;
		spawnEffectTime = 0.0f;
		spawnEffectCount++;
		if (spawnEffectCount == 13) {
			spawnEffectUpDown = true;
			spawnEffectCheck = false;
			spawnEffectTime = 0.0f;
			spawnEffectCount = 0;
			spawnEffectFrame = 0;
			spawnCheck = true;
		}
	}
}
