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

	float maxSpeed = 1.0f;
	float currSpeed = 0.0f;
	float speed = 0.01f;
	float resistance = 0.001f;

	float maxJumpPower = 2.0f;
	float currJumpPower = 0.0f;
	float jumpPower = 0.1f;
	float gravity = 0.001f;
	float maxGravity = 0.05f;
	float gravityAcceleration = 0.001f;

	bool isGround = true;
	bool jumpEnd = false;

	// 방향 가져야 함 ?
	MoveDirection direction = MoveDirection::Right;

	int frameX = 0;
	int frameY = 0;	// 방향의 역할도 함께 함

	bool isDead = false;

	int level = 1;		// 1 : small, 2 :  big, 3 : fire

	int nowTileIndexX = 0;
	int nowTileIndexY = 0;

	void UpdateCollider();
	bool OnCollisionEnter(RECT rc1, RECT rc2);
	void Jump();
	void Move();
	void PositionUpdater();

	void AnimationFrameChanger();
	void AnimationFrameChanger(int frameX, int frameY);	// 애니메이션 직접 변경할 때 사용

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~PlayerCharacter() = default;

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

