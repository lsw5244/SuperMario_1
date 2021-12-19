#pragma once
#include "Item.h"
#include "EnumClassCollection.h"

class Image;
class Mushroom : public Item
{
private:
	MoveDirection moveDirection = MoveDirection::Right;

	float speed = 50.0f;

	float gravity = 50.0f;

	void AutoMove();
	void ChangeDirection();
	bool CheckIsGround();

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual ~Mushroom() = default;

};

