#include "ItemManager.h"
#include "Mushroom.h"
#include "FireFlower.h"
#include "SpinCoin.h"
#include "MacroCollection.h"
#include "GameDataContainer.h"

HRESULT ItemManager::Init()
{
	mushroom = new Mushroom;
	mushroom->Init();

	fireFlower = new FireFlower;
	fireFlower->Init();

	spinCoin = new SpinCoin;
	spinCoin->Init();

	return S_OK;
}

void ItemManager::Update()
{
	mushroom->Update();
	fireFlower->Update();
	spinCoin->Update();
}

void ItemManager::Render(HDC hdc)
{
	mushroom->Render(hdc);
	fireFlower->Render(hdc);
	spinCoin->Render(hdc);
}

void ItemManager::Release()
{
	SAFE_RELEASE(mushroom);
	SAFE_RELEASE(fireFlower);
	SAFE_RELEASE(spinCoin);
}

void ItemManager::SpawnItem(POINTFLOAT pos)
{
	if (PLAYER->GetLevel() == 1)
	{
		mushroom->Spawn(pos);
	}
	else
	{
		fireFlower->Spawn(pos);
	}
}

void ItemManager::SpawnCoin(POINTFLOAT pos)
{
	spinCoin->Spawn(pos);
}
