#include "EnemyStatus.h"
#include "Image.h"
#include "StageManager.h"

HRESULT EnemyStatus::Init()
{
	enemyNumIcon = ImageManager::GetSingleton()->FindImage("Image/Icon/Icon_Enemy.bmp");
	totalEnmey = 20;
	return S_OK;
}

void EnemyStatus::Update()
{
	totalEnmey = 20 - stageManager->GetSpawnNum();
}

void EnemyStatus::Render(HDC hdc)
{
	for (int i = 0; i < totalEnmey; i++)
	{
		enemyNumIcon->Render(hdc, 235 + (8 * (i % 2)), 16 + (8 * (i / 2)));
	}
}

void EnemyStatus::Release()
{
}
