#pragma once
#include "GameEntity.h"
#include "HeaderCollection.h"
#include "EnumClassCollection.h"

class Image;
class PlayerCharacter : public GameEntity
{
private:
	//Image* img = ImageManager::GetSingleton()->FindImage("Image/Character/SamllRedMario.bmp");
	Image* img = ImageManager::GetInstance()->FindImage("Image/Character/SamllRedMario.bmp");
	
	POINTFLOAT pos = { 0, 0 };

	RECT collider = {};

	float maxSpeed				 = 240.0f;
	float currSpeed				 = 0.0f;
	float acceleration			 = 1.6f;
	float resistance			 = 1.6f;
	float jumpCorrectionSpeed	 = 1.2f;

	float maxJumpPower			 = 220.0f;
	float currJumpPower			 = 0.0f;
	float jumpPower				 = 1400.0f;

	float gravity				 = 300.0f;
	float maxGravity			 = 500.0f;
	float gravityAcceleration	 = 5000.0f;//5500.0f;

	bool isGround				 = true;
	bool jumpEnd				 = false;

	int frameX					 = 0;
	int frameY					 = 0;	// 방향의 역할도 함께 함

	float elapsedTime			 = 0.0f;
	float animationDelay		 = 0.15f;

	bool isDead					 = false;
	bool isGrowing				 = false;
	bool isSmalling				 = false;

	int nowImageIdChecker		 = 0;

	int level					 = 1;		// 1 : small, 2 :  big, 3 : fire

	int nowTileIndexX			 = 0;
	int nowTileIndexY			 = 0;

	void UpdateCollider();
	bool OnCollisionEnter(RECT plyaerRect, RECT tileRect);
	void Jump();
	void Move();
	void PositionUpdater();

	void ChagneAnimationFrame();
	void ChagneAnimationFrame(int frameX, int frameY);	// 애니메이션 직접 변경할 때 사용

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~PlayerCharacter() = default;

	void LevelUp();
	void Smalling();
	void Hit();

	void SetPos(POINTFLOAT pos)
	{
		this->pos = pos;
	}
	POINTFLOAT GetPos()
	{
		return this->pos;
	}

	float GetCurrSpeed()
	{
		return currSpeed;
	}
};

