#include "AmmoManager.h"
#include "FireAmmo.h"
#include "MacroCollection.h"

HRESULT AmmoManager::Init()
{
	ammos.resize(MAX_AMMO_COUNT);
	for (int i = 0; i < MAX_AMMO_COUNT; i++)
	{
		ammos[i] = new FireAmmo;
		ammos[i]->Init();
	}

	return S_OK;
}

void AmmoManager::Update()
{
	for (int i = 0; i < MAX_AMMO_COUNT; i++)
	{
		ammos[i]->Update();
	}
}

void AmmoManager::Render(HDC hdc)
{
	for (int i = 0; i < MAX_AMMO_COUNT; i++)
	{
		ammos[i]->Render(hdc);
	}
}

void AmmoManager::Release()
{
	for (vector<FireAmmo*>::iterator it = ammos.begin(); it != ammos.end(); ++it)
	{
		SAFE_RELEASE((*it));
	}
	ammos.clear();
}

bool AmmoManager::PlayerFire(POINTFLOAT pos, MoveDirection direction)
{
	for (int i = 0; i < MAX_AMMO_COUNT; i++)
	{
		if (ammos[i]->GetIsDead() == true)
		{
			ammos[i]->Fire(pos, direction);
			return true;
		}
	}

	return false;
}

bool AmmoManager::CheckCollideWithAmmo(RECT rect)
{
	for (int i = 0; i < MAX_AMMO_COUNT; i++)
	{
		if (ammos[i]->GetIsDead() == true)
		{
			continue;
		}
		if (OnCollisionEnter(rect, ammos[i]->GetCollider()) == true)
		{
			ammos[i]->SetIsExploding(true);
			return true;
		}
	}
	return false;
}

bool AmmoManager::OnCollisionEnter(RECT rc1, RECT rc2)
{
	if (rc1.left > rc2.right)	return false;
	if (rc1.right < rc2.left)	return false;
	if (rc1.top > rc2.bottom)	return false;
	if (rc1.bottom < rc2.top)	return false;

	return true;
}
