#pragma once
#include "GameEntity.h"

class FireAmmo;
class AmmoManger : public GameEntity
{
private:

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~AmmoManger();
};

