#include "ItemManager.h"
#include "Item.h"
#include "ItemManager.h"

void ItemManager::ActiveShoveItem()
{
	if (shovelTime == 0.0f) {
		SetIronBrick(25,11);
		SetIronBrick(24,11);
		SetIronBrick(23,11);
		SetIronBrick(23,12);
		SetIronBrick(23,13);
		SetIronBrick(23,14);
		SetIronBrick(24,14);
		SetIronBrick(25,14);
	}

	shovelTime += TimerManager::GetSingleton()->GetDeltaTime();
	if (shovelTime >= 10.0f) {
		shovelUse = false;
		shovelTime = 0.0f;
		SetBrick(25, 11);
		SetBrick(24, 11);
		SetBrick(23, 11);
		SetBrick(23, 12);
		SetBrick(23, 13);
		SetBrick(23, 14);
		SetBrick(24, 14);
		SetBrick(25, 14);
	}
}

void ItemManager::SetIronBrick(int y, int x)
{
	tileInfo[y][x].terrain = ::Terrain::IronBrick;
	tileInfo[y][x].frameX[0] = 0;
	tileInfo[y][x].frameY[0] = 6;
	tileInfo[y][x].frameX[1] = 1;
	tileInfo[y][x].frameY[0] = 6;
	tileInfo[y][x].frameX[0] = 0;
	tileInfo[y][x].frameY[1] = 7;
	tileInfo[y][x].frameX[1] = 1;
	tileInfo[y][x].frameY[1] = 7;
	tileInfo[y][x].isDes[0][0] = true;
	tileInfo[y][x].isDes[0][1] = true;
	tileInfo[y][x].isDes[1][0] = true;
	tileInfo[y][x].isDes[1][1] = true;
}

void ItemManager::SetBrick(int y, int x)
{
	tileInfo[y][x].terrain = ::Terrain::Brick;
	tileInfo[y][x].frameX[0] = 0;
	tileInfo[y][x].frameY[0] = 0;
	tileInfo[y][x].frameX[1] = 1;
	tileInfo[y][x].frameY[0] = 0;
	tileInfo[y][x].frameX[0] = 0;
	tileInfo[y][x].frameY[1] = 1;
	tileInfo[y][x].frameX[1] = 1;
	tileInfo[y][x].frameY[1] = 1;
	tileInfo[y][x].isDes[0][0] = true;
	tileInfo[y][x].isDes[0][1] = true;
	tileInfo[y][x].isDes[1][0] = true;
	tileInfo[y][x].isDes[1][1] = true;
}

void ItemManager::newItem()
{
	vecItems.push_back(new Item);
	vecItems.back()->Init(*playerTank, *enemyTankManager, *itemManager);
}

HRESULT ItemManager::Init()
{
	shovelUse = false;
	shovelTime = 0.0f;
	itemManager = this;
	eraseCount = 0;
	return S_OK;
}

void ItemManager::Update()
{
	for (vector<Item*>::iterator it = vecItems.begin();
		it != vecItems.end();)
	{
		if ((*it)->ItemUpdate()) 
		{
			SAFE_RELEASE((*it));
			it = vecItems.erase(it);
		}
		else {
			it++;
		}
	}
	if (shovelUse) ActiveShoveItem();
}

void ItemManager::Render(HDC hdc)
{
	for (vector<Item*>::iterator it = vecItems.begin();
		it != vecItems.end();
		it++)
	{
		(*it)->Render(hdc);
	}
}

void ItemManager::Release()
{
	for (vector<Item*>::iterator it = vecItems.begin();
		it != vecItems.end();)
	{
		SAFE_RELEASE((*it));
		it = vecItems.erase(it);
	}
	vecItems.clear();
}

void ItemManager::Setdata(PlayerTank& playerTank, EnemyTankManager& enemyTankManager, TILE_INFO(*tileInfo)[TILE_COUNT])
{
	this->playerTank = &playerTank;
	this->enemyTankManager = &enemyTankManager;
	this->tileInfo = tileInfo;
}
