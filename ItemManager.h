#pragma once
#include "GameEntity.h"
#include <vector>

class Mushroom;
class FireFlower;
class SpinCoin;

class ItemManager : public GameEntity
{
private:
	Mushroom* mushroom;
	FireFlower* fireFlower;
	SpinCoin* spinCoin;

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual ~ItemManager() = default;

	void SpawnItem(POINTFLOAT pos);
	void SpawnCoin(POINTFLOAT pos);
};

