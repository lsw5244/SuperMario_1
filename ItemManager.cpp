#include "ItemManager.h"
#include "Mushroom.h"
#include "FireFlower.h"
#include "MacroCollection.h"
HRESULT ItemManager::Init()
{
	mushroom = new Mushroom;
	mushroom->Init();

	fireFlower = new FireFlower;
	fireFlower->Init();

	return S_OK;
}

void ItemManager::Update()
{
	mushroom->Update();
	fireFlower->Update();
}

void ItemManager::Render(HDC hdc)
{
	mushroom->Render(hdc);
	fireFlower->Render(hdc);
}

void ItemManager::Release()
{
	SAFE_RELEASE(mushroom);
	SAFE_RELEASE(fireFlower);
}
