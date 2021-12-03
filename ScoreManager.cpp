#include "ScoreManager.h"
#include "EnemyTankManager.h"
#include "PlayerTank.h"
#include "Config.h"
#include "GameDataManager.h"

void ScoreManager::Init()
{
	totalNormal = 0;
	totalFastMove = 0;
	totalFastShoot = 0;
	totalBigTank = 0;
	totalDestroy = 0;
	itemBonusPoint = 0;
}

void ScoreManager::Release()
{

}

void ScoreManager::Update(PlayerTank& playerTank, EnemyTankManager& enemyTank)
{
	totalNormal = enemyTank.GetTotalNormal();
	totalFastMove = enemyTank.GetTotalFastMove();
	totalFastShoot = enemyTank.GetTotalFastShoot();
	totalBigTank = enemyTank.GetTotalBigTank();
	itemBonusPoint = enemyTank.GetItemBonusPoint();

	if (enemyTank.GetCheckScore())
	{
		switch (enemyTank.GetReturnScore())
		{
		case 100:
			totalScore += 100;
			prevTotalScore += 100;
		
			break;
		case 200:
			totalScore += 200;
			prevTotalScore += 200;
			break;
		case 300:
			totalScore += 300;
			prevTotalScore += 300;
			break;
		case 400:
			totalScore += 400;
			prevTotalScore += 400;
			break;
		}
		enemyTank.SetCheckScore(false);
	}
	if (playerTank.GetGetItem() == true)
	{
		totalScore += 500;
		prevTotalScore += 500;
		playerTank.SetGetItem(false);
	}
	
	totalDestroy = totalNormal + totalFastMove + totalFastShoot + totalBigTank;

	if (totalScore > 20000) {
		GameDataManager::GetSingleton()->SetPlayerLife(GameDataManager::GetSingleton()->GetPlayerLife() + 1);
		totalScore = totalScore - 20000;
	}
	if (prevTotalScore > 1000000) prevTotalScore = prevTotalScore - 1000000;
}

void ScoreManager::Render(HDC hdc)
{
}

void ScoreManager::SetData(PlayerTank& playerTank, EnemyTankManager& enemyTank)
{
	SetPlayerTank(playerTank);
	SetEnemyTank(enemyTank);
}
