#pragma once
#include "GameEntity.h"
#include <vector>

class FireAmmo;
class AmmoManger : public GameEntity
{
private:
	std::vector<FireAmmo*> ammos;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~AmmoManger() = default;
};

