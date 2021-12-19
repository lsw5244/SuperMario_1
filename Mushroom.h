#pragma once
#include "GameEntity.h"
#include "EnumClassCollection.h"
#include "HeaderCollection.h"

class Image;
class Mushroom : public GameEntity
{
private:
	Image* img = ImageManager::GetInstance()->FindImage("Image/Item/Mushroom.bmp");

	POINTFLOAT pos = {};
	MoveDirection moveDirection = MoveDirection::Right;

	RECT collider = {};

	float speed = 50.0f;

	float gravity = 50.0f;

	bool isDead = false;
	
	bool isGround = false;

	int nowTileIndexX = 0;
	int nowTileIndexY = 0;

	void AutoMove();
	void UpdateCollider();
	bool OnCollisionEnter(RECT plyaerRect, RECT tileRect);
	void ChangeDirection();
	bool CheckIsGround();

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual ~Mushroom() = default;

};

