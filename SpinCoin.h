#pragma once
#include "Item.h"

class SpinCoin : public Item
{
private:
	int frameX = 0;

	float elapsedTime = 0.0f;
	float animationDelay = 0.05f;


	void ChangeFrame();
public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual ~SpinCoin() = default;
};

