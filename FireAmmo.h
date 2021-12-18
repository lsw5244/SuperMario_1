#pragma once
#include "GameEntity.h"
#include "HeaderCollection.h"
#include "EnumClassCollection.h"

class Image;
class FireAmmo : public GameEntity
{
private:
	Image* img = ImageManager::GetInstance()->FindImage("Image/Particle/AttackFireAndExplosion.bmp");

	int frameX = 0;
	POINTFLOAT pos = {};
	RECT collider = {};

	int nowTileIndexX = 0;
	int nowTileIndexY = 0;

	bool isDead = false;
	bool isExploding = false;

	float speed = 250.0f;

	const float maxJumpHeight = 20.0f;
	float jumpHeight = 0.0f;

	float elapsedTime = 0.0f;

	BoundDirection boundDirection = BoundDirection::Down;
	MoveDirection moveDirection = MoveDirection::Right;

	void UpdateCollider();
	bool OnCollisionEnter(RECT rc1, RECT rc2);
	void ChangeAnimationFrame();
	void ChangeBoundDirection();
	void UpdatePosition();
	void Explosion();
	void ReSpawn();
	void Destroy();

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~FireAmmo() = default;

	bool GetIsDead()
	{
		return isDead;
	}

	void Fire(POINTFLOAT pos, MoveDirection direction);
};

