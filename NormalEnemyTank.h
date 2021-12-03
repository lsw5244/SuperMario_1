#pragma once
#include "EnemyTanks.h"
class NormalEnemyTank : public EnemyTanks
{
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~NormalEnemyTank() = default;
	void AutoFire() override;
};

