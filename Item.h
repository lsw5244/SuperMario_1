#pragma once
#include "Config.h"
#include "GameObject.h"
#include "PlayerTank.h"

class ItemManager;
class EnemyTankManager;
class Item : public GameObject
{
private:
	enum class ItemState { Barrier, TimeStop, Shovel, Star, Boom, Life };
	EnemyTankManager* enemyTankManager;
	PlayerTank* playerTank;
	RECT* playerRect;
	ItemState itemState;
	ItemManager* itemManager;
	float aliveTime;
	float renderTime;
	int itemNum;
	bool collCheck; 

	Image* pointImage;
	bool getItemCheck;
	float pointImageTime;
	bool pointImageRender;

	inline void SetPlyaerRect(PlayerTank& playerTank) { this->playerRect = playerTank.GetRect(); }
	inline void SetPlyaer(PlayerTank& playerTank) { this->playerTank = &playerTank; }
	inline void SetEnemyTankManager(EnemyTankManager& enemyTankManager) { this->enemyTankManager = &enemyTankManager; }
	inline void SetItemManager(ItemManager& itemManager) { this->itemManager = &itemManager; }

protected:
public:
	bool ItemUpdate();
	HRESULT Init(PlayerTank& playerTank, EnemyTankManager& enemyTankManager, ItemManager& itemManager);
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~Item() = default;
};

