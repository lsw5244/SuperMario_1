#pragma once
#include "Item.h"

class FireFlower : public Item
{
private:
	int frameX = 0;
	const int lastFrameX = 3;

	float elapsedTime = 0.0f;
	float animationDelay = 0.05f;

	void ChangeFrame();
	//void SpawnAnimation();
public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual ~FireFlower() = default;

	void AutoMove();
	//void Spawn(POINTFLOAT pos);
};

