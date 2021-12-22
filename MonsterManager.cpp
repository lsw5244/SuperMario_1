#include "MonsterManager.h"
#include "Gunba.h"

#define MONSTER_MAX_COUNT 10

HRESULT MonsterManager::Init()
{
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
	for (int i = 0; i < MONSTER_MAX_COUNT; i++)
	{
		delete monsters[i];
		monsters[i] = nullptr;
	}

	monsters.clear();
}
