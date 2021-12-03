#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "PlayerTank.h"
#include "EnemyTankManager.h"
class Item;
class ItemManager : public  GameEntity
{
private:
	vector<Item*> vecItems;
	ItemManager* itemManager;
	int eraseCount;

	TILE_INFO(*tileInfo)[TILE_COUNT];
	PlayerTank* playerTank;
	EnemyTankManager* enemyTankManager;

	bool shovelUse;
	float shovelTime;
	void ActiveShoveItem();
	void SetIronBrick(int x, int y);
	void SetBrick(int x, int y);
protected:

public:
	void newItem();
	void Setdata(PlayerTank& playerTank, EnemyTankManager& enemyTankManager, TILE_INFO(*tileInfo)[TILE_COUNT]);
	void ActiveShove() { shovelUse = true, shovelTime = 0.0f; }
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~ItemManager() = default;
};

