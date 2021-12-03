#pragma once
#include "Config.h"
#include "GameEntity.h"

class PlayerStatus;
class PlayerTank;
class EnemyStatus;
class StageManager;
class UIManager : public GameEntity
{
private:
	PlayerStatus* playerStatus;
	EnemyStatus* enemyStatus;

public:
	void SetData(PlayerTank* playerTank, StageManager* stageManager);
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~UIManager() = default;

};

