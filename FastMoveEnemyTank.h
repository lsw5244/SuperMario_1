#pragma once
#include "EnemyTanks.h"
class FastMoveEnemyTank : public EnemyTanks
{
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~FastMoveEnemyTank() = default;
	void AutoFire() override;
};

