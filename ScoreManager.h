#pragma once
#include "Config.h"
#include "Singleton.h"

class PlayerTank;
class EnemyTankManager;
class EnemyTanks;
class ScoreManager : public Singleton<ScoreManager>
{
private:
	PlayerTank* playerTank;
	EnemyTankManager* enemyTanks;
	int totalNormal;
	int totalFastMove;
	int totalFastShoot;
	int totalBigTank;
	int totalDestroy;
	int itemBonusPoint;
	int totalScore;
	int prevTotalScore;
	bool isDestruction;


	//TILE_INFO tileInfo[TILE_COUNT][TILE_COUNT] ;
	//bool playerIsDead;		// 플레이어가 패배했을 경우
	//int isStage = 1;		// 현재 스테이지
	//int playerLife = 2;		// 플레이어 라이프
	//int playerLevel = 0;	// 플레이어 레벨

	inline void SetPlayerTank(PlayerTank& playerTank) { this->playerTank = &playerTank; }
	inline void SetEnemyTank(EnemyTankManager& enemyTank) { this->enemyTanks = &enemyTank; }
public:
	void Init();
	void Release();
	void Update(PlayerTank& playerTank, EnemyTankManager& enemyTank);
	void Render(HDC hdc);

	void SetData(PlayerTank& playerTank, EnemyTankManager& enemyTank);




	//inline void SetPlayerLife(int playerLife) { this->playerLife = playerLife; }
	//inline int GetPlayerLife() { return playerLife; }

	//inline void SetPlayerLevel(int playerLevel) { this->playerLevel = playerLevel; }
	//inline int GetPlayerLevel() { return playerLevel; }

	//inline void SetPlayerIsDead(bool playerIsDead) { this->playerIsDead = playerIsDead; }
	//inline bool GetPlayerIsDead() { return playerIsDead; }
	//
	//inline void SetStage(int stageNum) { this->isStage = stageNum; }
	//inline void AddIsStage() { if(isStage<11)this->isStage++; }
	//inline int GetIsStage() { return isStage; }

	//inline void SetTileInfo(TILE_INFO tileInfo, int y, int x) { this->tileInfo[y][x] = tileInfo; }
	//inline TILE_INFO GetTileInfo(int y, int x) { return tileInfo[y][x]; }


	inline int GetTotalNormal() { return totalNormal; }
	inline int GetTotalFastMove() { return totalFastMove; }
	inline int GetTotalFastShoot() { return totalFastShoot; }
	inline int GetTotalBigTank() { return totalBigTank; }
	inline int GetTotalDestroy() { return totalDestroy; }
	inline int GetTotalScore() { return totalScore; }
	inline int GetPrevTotalScore() { return prevTotalScore; }
	inline bool GetisDestruction() { return this->isDestruction; }

};

