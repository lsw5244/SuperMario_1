#pragma once
#include "GameEntity.h"
#include "EnumClassCollection.h"
#include <vector>

#define MAX_AMMO_COUNT 2
class FireAmmo;
class AmmoManager : public GameEntity
{
private:
	std::vector<FireAmmo*> ammos;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~AmmoManager() = default;

	bool PlayerFire(POINTFLOAT pos, MoveDirection direction);
};

