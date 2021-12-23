#include "MonsterManager.h"
#include "Gunba.h"
#include "GameDataContainer.h"

#define MONSTER_MAX_COUNT 10

HRESULT MonsterManager::Init()
{
	monsterWave = 0;
	monsters.resize(MONSTER_MAX_COUNT);

	for (int i = 0; i < MONSTER_MAX_COUNT; i++)
	{
		monsters[i] = new Gunba;
		monsters[i]->Init();
	}

	return S_OK;
}

void MonsterManager::Update()
{
	if (spawnGlobalPos[monsterWave] < GLOBAL_POS && monsterWave < MAX_MONSTER_WAVE_COUNT - 1)
	{
		SpawnMonster({ WIN_SIZE_X - 10, spawnYpos[monsterWave] });
		++monsterWave;
	}

	for (int i = 0; i < MONSTER_MAX_COUNT; i++)
	{
		monsters[i]->Update();
	}
}

void MonsterManager::Render(HDC hdc)
{
	for (int i = 0; i < MONSTER_MAX_COUNT; i++)
	{
		monsters[i]->Render(hdc);
	}
}

void MonsterManager::Release()
{
	for (vector<Gunba*>::iterator it = monsters.begin(); it != monsters.end(); ++it)
	{
		SAFE_RELEASE((*it));
	}

	monsters.clear();
}

void MonsterManager::SpawnMonster(POINTFLOAT pos)
{
	for (int i = 0; i < MONSTER_MAX_COUNT; i++)
	{
		if (monsters[i]->GetIsDead() == true)
		{
			monsters[i]->Spawn(pos);
			return;
		}	
	}
}
