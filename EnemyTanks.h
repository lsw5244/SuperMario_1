#pragma once
#include "GameObject.h"
#include "Config.h"
#include "Image.h"
#include "ImageManager.h"
#include <tuple>
#include "PlayerTank.h"
#include "ItemManager.h"

class AmmoManager;
class ItemManager;
class EnemyTanks : public GameObject
{
private:
protected:
	vector<EnemyTanks*> vecEnemyTanks;

	AmmoManager* ammoManager;
	ItemManager* itemManager;


	TankInfo tankinfo;
	bool isItemDes;
	bool boomItemCheck;
	
	void CollisionAndMove(MoveDir moveDir);
	void PosReset(MoveDir moveDir);
	void TankUpdate();

	int itemTankImg(int num);
	float itemTime;
	int itemfraemY;
	int hp;
	int CurrFrame(Image enemyTank, int* elapsedCount, int setCurr);
	tuple<MoveDir, bool> AutoMove(MoveDir moveDir, POINTFLOAT pos);
	TILE_INFO(*tileInfo)[TILE_COUNT];
	bool spawnColl;		// 스폰시 다른 탱크와 겹쳐있는지 여부
	bool itemTank;		// 아이템을 소유하고 있는 탱크인지 여부

	RECT* playerRect;
	MoveDir movedir;
	int elapsedWay;
	int elapsedCount;
	float time;

	Image* destructionEffect1;
	int destructionEffectNum;
	float destructionEffectTime;
	bool isDestructionEffect;
	bool isDestruction;
	bool timeStop;

	Image* pointImage;
	float attackDelayTime = 0.0f;
	int attackDelay = 1;
	TankType type = TankType::Enemy;

public:
	inline TankInfo GetTankInfo() { return this->tankinfo; }
	inline void SetItemManager(ItemManager* itemManager) { this->itemManager = itemManager; }
	inline void SetTileInfo(TILE_INFO(*tileInfo)[TILE_COUNT]) { this->tileInfo = tileInfo; }
	inline void SetPlyaerRect(PlayerTank& playerTank) { this->playerRect = playerTank.GetRect(); }
	inline void SetAmmoMgr(AmmoManager* mgr) { ammoManager = mgr; }
	inline bool GetItemDes() { return isItemDes; }
	inline void isHit() { this->hp = hp-1; if (hp <= 0) isDestructionEffect = true; }
	inline void BoomItem() { this->hp = 0, isDestructionEffect = true, boomItemCheck = true, isItemDes = true; }

	inline void SetVecEnemyTank(vector<EnemyTanks*> vecEnemyTank) { this->vecEnemyTanks = vecEnemyTank; }
	inline bool GetisDestruction() {return this->isDestruction;}
	inline void SetTimeStop(bool timeStop) {this->timeStop = timeStop;}
	inline RECT GetRect() { return this->shape; }
	inline int GetHp() { return hp; }
	
	HRESULT TankInit(int posX, bool item);
	virtual HRESULT Init() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release() = 0;
	virtual ~EnemyTanks() = default;
	virtual void AutoFire() = 0;
};

