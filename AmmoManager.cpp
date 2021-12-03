/*
	주의 ! : AmmoManager는 Init하기 전에 SetTileInfo를 먼저 해 주어야 함 !
*/

#include "AmmoManager.h"
#include "Ammo.h"

HRESULT AmmoManager::Init()
{
	for (int i = 0; i < PLAYER_MAX_AMMO_COUNT; i++)
	{
		playerAmmos[i] = new Ammo;
		playerAmmos[i]->Init();
		playerAmmos[i]->SetTileInfo(tileInfo);
		playerAmmos[i]->SetType(TankType::Player);
		playerAmmos[i]->SetPlayerTank(playerTank);
		playerAmmos[i]->SetVecEnemyTank(vecEnemys);
	}

	vecEnemyAmmos.resize(enemyMaxAmmoCount);
	for (vector<Ammo*>::iterator it = vecEnemyAmmos.begin(); it != vecEnemyAmmos.end(); it++)
	{
		(*it) = new Ammo;
		(*it)->Init();
		(*it)->SetTileInfo(tileInfo);
		(*it)->SetType(TankType::Enemy);
		(*it)->SetPlayerTank(playerTank);
		(*it)->SetVecEnemyTank(vecEnemys);
		(*it)->SetPlayerAmmos(playerAmmos);
	}

	return S_OK;
}

void AmmoManager::Update()
{
	for (vector<Ammo*>::iterator it = vecEnemyAmmos.begin(); it != vecEnemyAmmos.end(); it++)
	{
		(*it)->Update();
	}

	for (int i = 0; i < PLAYER_MAX_AMMO_COUNT; i++)
	{
		playerAmmos[i]->Update();
	}
}

void AmmoManager::Render(HDC hdc)
{
	for (vector<Ammo*>::iterator it = vecEnemyAmmos.begin(); it != vecEnemyAmmos.end(); it++)
	{
		(*it)->Render(hdc);
	}

	for (int i = 0; i < PLAYER_MAX_AMMO_COUNT; i++)
	{
		playerAmmos[i]->Render(hdc);
	}
}

void AmmoManager::Release()
{
	for (vector<Ammo*>::iterator it = vecEnemyAmmos.begin(); it != vecEnemyAmmos.end(); it++)
	{
		SAFE_RELEASE((*it));
	}
	vecEnemyAmmos.clear();

	for (int i = 0; i < PLAYER_MAX_AMMO_COUNT; i++)
	{
		SAFE_RELEASE(playerAmmos[i]);
	}
}

void AmmoManager::Fire(MoveDir dir, POINTFLOAT pos, TankType type, bool isFastAmmo, int maxAmmo)
{
	switch (type)
	{
	case TankType::Player:
		for (int i = 0; i < maxAmmo; i++)
		{
			if (playerAmmos[i]->GetIsAlive() == false && playerAmmos[i]->GetRenderBoomEffect() == false)
			{
				playerAmmos[i]->Fire(dir, pos, isFastAmmo);
				break;
			}
		}
		break;
	case TankType::Enemy:
		for (vector<Ammo*>::iterator it = vecEnemyAmmos.begin(); it != vecEnemyAmmos.end(); it++)
		{
			if ((*it)->GetIsAlive() == false && (*it)->GetRenderBoomEffect() == false)
			{
				(*it)->Fire(dir, pos, isFastAmmo);
				break;
			}
		}
		break;
	default:
		break;
	}
}


void AmmoManager::SetTileInfoAndEnemyVec()
{
	for (int i = 0; i < PLAYER_MAX_AMMO_COUNT; i++)
	{
		playerAmmos[i]->SetPlayerTank(playerTank);
		playerAmmos[i]->SetVecEnemyTank(vecEnemys);
	}
}

//void AmmoManager::SetPlayerTankDestroyIronBrick()
void AmmoManager::PlayerAmmoPowerUp()
{
	for (int i = 0; i < PLAYER_MAX_AMMO_COUNT; i++)
	{
		playerAmmos[i]->SetCanDestroyIronWall(true);
	}
}

void AmmoManager::PlayerAmmoPowerDown()
{
	for (int i = 0; i < PLAYER_MAX_AMMO_COUNT; i++)
	{
		playerAmmos[i]->SetCanDestroyIronWall(false);
	}
}
