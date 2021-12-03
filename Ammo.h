#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class PlayerTank;
class EnemyTanks;
class AmmoManager;
class Ammo : public GameObject
{
private:
	MoveDir dir;
	bool isAlive = false;
	bool renderBoomEffect;
	bool showCollider;

	float sec;
	POINT baseStartPoint;
	int boomEffectFrameX;

	Image* boomEffect;

	TILE_INFO(*tileInfo)[TILE_COUNT];

	TILE_INFO* hitTile1;
	TILE_INFO* hitTile2;

	bool isHit;

	RECT gameSceneRect;

	TankType type;

	PlayerTank* playerTank;
	vector<EnemyTanks*> vecEnemys;

	Ammo** playerAmmos;

	bool canDestroyIronWall;

	bool isFastAmmo = false;
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~Ammo() = default;

	void Fire(MoveDir dir, POINTFLOAT pos, bool isFastAmmo = false);
	void DestroyAmmo();
	void EraseAmmo();

	void SetTileInfo(TILE_INFO(*info)[TILE_COUNT]) { this->tileInfo = info; }
	void SetPlayerAmmos(Ammo** ammos) { playerAmmos = ammos; }

	void AmmoHitCheck();
	void DestroyWall(TILE_INFO* tileInfo);
	void DestroyWall(TILE_INFO* tileInfo1, TILE_INFO* tileinfo2);
	void PowerAmmoDestroyWall(TILE_INFO* tileInfo1, TILE_INFO* tileinfo2);
	void PowerAmmoDestroyWall(TILE_INFO* tileInfo1);

	void IronWallHitDestroyWall(TILE_INFO* tileInfo);
	void DestroyBase();

	inline bool GetIsAlive() { return isAlive; }
	inline bool GetRenderBoomEffect() { return renderBoomEffect; }
	inline void SetType(TankType type) { this->type = type; }
	inline void SetPlayerTank(PlayerTank* tank) { playerTank = tank; }
	inline void SetVecEnemyTank(vector<EnemyTanks*> vecEnemyTank) { this->vecEnemys = vecEnemyTank; }
	inline void SetCanDestroyIronWall(bool canDestroyIronWall) { this->canDestroyIronWall = canDestroyIronWall; }
	bool CollisionEnter(RECT rc1, RECT rc2);
	RECT GetRect() { return shape; }
};