#pragma once
#include "GameEntity.h"
#include <vector>

class Gunba;
class MonsterManager : public GameEntity
{
private:
	std::vector<Gunba*> monsters;

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual ~MonsterManager() = default;

	void SpawnMonster(POINTFLOAT pos);
};

