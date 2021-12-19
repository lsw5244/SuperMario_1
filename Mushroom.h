#pragma once
#include "GameEntity.h"

class Mushroom : public GameEntity
{
private:

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual ~Mushroom() = default;

};

