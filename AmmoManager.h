#pragma once
#include "Config.h"
#include "GameEntity.h"

class Ammo;
class PlayerTank;
class EnemyTanks;
#define PLAYER_MAX_AMMO_COUNT 2
class AmmoManager : public GameEntity
{
private:
	vector<Ammo*> vecEnemyAmmos;
	vector<EnemyTanks*> vecEnemys;

	int enemyMaxAmmoCount = 30;

	Ammo* playerAmmos[PLAYER_MAX_AMMO_COUNT];

	TILE_INFO(*tileInfo)[TILE_COUNT];

	PlayerTank* playerTank;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~AmmoManager() = default;

	void Fire(MoveDir dir, POINTFLOAT pos, TankType type, bool isFastAmmo = false, int maxAmmo = 1);
	void SetTileInfoAndEnemyVec();

	void SetTileInfo(TILE_INFO(*info)[TILE_COUNT]) { this->tileInfo = info; }
	inline void SetPlayerTank(PlayerTank* tank) { playerTank = tank; }
	inline void SetVecEnemyTank(vector<EnemyTanks*> vecEnemyTank) { this->vecEnemys = vecEnemyTank; }

	void PlayerAmmoPowerUp();
	void PlayerAmmoPowerDown();

};

