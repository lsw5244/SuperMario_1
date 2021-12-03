#pragma once
#include "Config.h"
#include "GameEntity.h"

class Image;
class PlayerCharacter : public GameEntity
{
private:
	Image* img = ImageManager::GetSingleton()->FindImage("Image/SamllRedMario.bmp");
	POINTFLOAT pos = { 0, 0 };

	float maxSpeed = 1.0f;
	float currSpeed = 0.0f;
	float speed = 0.1f;

	float maxJumpPower = 4.5f;
	float currJumpPower = 0.0f;
	float jumpPower = 1.0f;

	float gravity = 0.1f;
	float resistance = 0.02f;

	bool isGround = true;
	bool jumpEnd = false;

	// 방향 가져야 함 ?
	MoveDirection direction = MoveDirection::Right;

	int frameX = 0;
	int frameY = 0;

	bool isDead = false;

	int level = 1;		// 1 : small, 2 :  big, 3 : fire

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
};

