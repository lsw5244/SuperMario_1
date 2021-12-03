#pragma once
#include "EnemyTanks.h"

class Image;
class StageManager;
class EnemyStatus : public GameEntity
{
private:
	Image* enemyNumIcon;
	StageManager* stageManager;

	int totalEnmey;
public:
	inline void SetData(StageManager* stageManager) { this->stageManager = stageManager; }
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual ~EnemyStatus() = default;
};

