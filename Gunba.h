#pragma once
#include "GameEntity.h"
#include "HeaderCollection.h"

class Image;
class Gunba : public GameEntity
{
private:
	Image* img = ImageManager::GetInstance()->FindImage("Image/Monster/Gunba.bmp");

	POINTFLOAT pos = { 0,0 };

	RECT collider = {};

	int frameX = 0;
	int frameY = 1;	// 기본적으로 왼쪽을 향함

	float speed = -60.0f; // 기본적으로 왼쪽을 향함

	float gravity = 100.0f;
	float maxGravity = 500.0f;
	float gravityAcceleration = 5000.0f;//5500.0f;

	float elapsedTime = 0.0f;

	bool isGround = false;
	bool isDead = false;

	int nowTileIndexX = 0;
	int nowTileIndexY = 0;

	void ChangeDirection();
	void ChangeAnimationFrame();
	void UpdateCollider();

	bool OnCollisionEnter(RECT rect, RECT tileRect);
	void CheckIsGround();
	void CheckOutWindow();

	bool CollideWithPlayer();	

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~Gunba() = default;

	void SetPos(POINTFLOAT pos) { this->pos = pos; }
	POINTFLOAT GetPos() { return pos; }
};

