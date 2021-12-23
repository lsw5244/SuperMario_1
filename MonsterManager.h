#pragma once
#include "GameEntity.h"
#include "MacroCollection.h"
#include <vector>

#define MAX_MONSTER_WAVE_COUNT 14
class Gunba;
class MonsterManager : public GameEntity
{
private:
	std::vector<Gunba*> monsters;

	int monsterWave = 0;
	float spawnYpos[MAX_MONSTER_WAVE_COUNT] = { WIN_SIZE_Y - TILE_SIZE * 3, WIN_SIZE_Y - TILE_SIZE * 3,
		TILE_SIZE * 4, TILE_SIZE * 4, 
		WIN_SIZE_Y - TILE_SIZE * 3, 
		WIN_SIZE_Y - TILE_SIZE * 3, WIN_SIZE_Y - TILE_SIZE * 3,
		WIN_SIZE_Y - TILE_SIZE * 3, WIN_SIZE_Y - TILE_SIZE * 3,
		WIN_SIZE_Y - TILE_SIZE * 3, WIN_SIZE_Y - TILE_SIZE * 3,
		WIN_SIZE_Y - TILE_SIZE * 3, WIN_SIZE_Y - TILE_SIZE * 3
	};
	float spawnGlobalPos[MAX_MONSTER_WAVE_COUNT] = { 550.0f, 550.0f + TILE_SIZE,
		1030.0f, 1030.0f + TILE_SIZE,
		1500.0f,
		1648.0f, 1648.0f + TILE_SIZE,
		1789.0f, 1789.0f + TILE_SIZE,
		1877.0f, 1877.0f + TILE_SIZE,
		2497.0f, 2497.0f + TILE_SIZE
	};

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual ~MonsterManager() = default;

	void SpawnMonster(POINTFLOAT pos);
};

