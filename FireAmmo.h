#pragma once
#include "GameEntity.h"
#include "HeaderCollection.h"

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

	float speed = 1.0f;
	float jumpSpeed = 1.0f;

	const float maxJumpHeight = 5.0f;
	float jumpHeight = 0.0f;

	float elapsedTime = 0.0f;

	void UpdateCollider();
	bool OnCollisionEnter(RECT rc1, RECT rc2);
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~FireAmmo() = default;
};

