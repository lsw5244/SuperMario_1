#pragma once
#include "PlayerTank.h"
#include "GameEntity.h"
class Iamge;
class PlayerTank;
class PlayerStatus : public GameEntity
{
private:
	Image* player1LifeImage;
	//	Image* player2LifeImage;
	Image* lifeNumImage;

	PlayerTank* playerTank;

public:
	void SetData(PlayerTank* playerTank);
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~PlayerStatus() = default;

	void ChangeLifeImage(int life);
};

