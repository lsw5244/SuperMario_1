#include "AmmoManger.h"
#include "FireAmmo.h"
#include "MacroCollection.h"

HRESULT AmmoManger::Init()
{
	ammos.resize(MAX_AMMO_COUNT);
	for (int i = 0; i < MAX_AMMO_COUNT; i++)
	{
		ammos[i] = new FireAmmo;
	}

	return S_OK;
}

void AmmoManger::Update()
{
	for (int i = 0; i < MAX_AMMO_COUNT; i++)
	{
		ammos[i]->Update();
	}
}

void AmmoManger::Render(HDC hdc)
{
	for (int i = 0; i < MAX_AMMO_COUNT; i++)
	{
		ammos[i]->Render(hdc);
	}
}

void AmmoManger::Release()
{
	for (vector<FireAmmo*>::iterator it = ammos.begin(); it != ammos.end(); ++it)
	{
		SAFE_RELEASE((*it));
	}
	ammos.clear();
}
