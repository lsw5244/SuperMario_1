#pragma once
#include "EnemyTanks.h"
class BigEnemyTank : public EnemyTanks
{
private:
	int bigTankFrame;
	bool renderChange;
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~BigEnemyTank() = default;
	void AutoFire() override;
};

