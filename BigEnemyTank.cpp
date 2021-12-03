#include "BigEnemyTank.h"
#include "AmmoManager.h"

HRESULT BigEnemyTank::Init()
{
	tankinfo = TankInfo::BigTank;
	attackDelay = rand() % 3 + 1;
	bigTankFrame = 5;
	if (itemTank) {
		img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy_Item.bmp");
		itemTime = 0.0f;
		itemfraemY = 6;
	} else {
		img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	}
	moveSpeed = 50;
	hp = 4;
	renderChange = true;
	return S_OK;
}

void BigEnemyTank::Update()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown('Q'))isHit();
	if (!isDestructionEffect) {
		if (!timeStop) {
			AutoFire();
			TankUpdate();
		}
	}
	else {
		destructionEffectTime += TimerManager::GetSingleton()->GetDeltaTime();
		shape.left = pos.x + 8;
		shape.top = pos.y + 8;
		shape.right = pos.x - 8;
		shape.bottom = pos.y - 8;
		if (destructionEffectTime >= 0.05f) {
			destructionEffectNum++;
			if (destructionEffectNum >= 16) {
				isDestruction = true;
				if (itemTank)itemManager->newItem();
			}
			destructionEffectTime = 0;
		}
	}

	if (hp == 3 &&itemTank && renderChange) {
		renderChange = false;
		img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	}
	if (hp == 1)bigTankFrame = 3;
	if (hp == 2){
		if (bigTankFrame >= 5) {
			bigTankFrame = 4;
		}
		else {
			bigTankFrame = 5;
		}
	}
	if (hp == 3){
		if (bigTankFrame >= 4) {
			bigTankFrame = 3;
		}
		else {
			bigTankFrame = 5;
		}
	}
	if (hp == 4) {
		if (bigTankFrame >= 4) {
			bigTankFrame = 3;
		}
		else {
			bigTankFrame = 4;
		}
	}


}

void BigEnemyTank::Render(HDC hdc)
{
	if (!isDestructionEffect) {
		if (KeyManager::GetSingleton()->IsStayKeyDown(TANK_COLLIDER_DEBUG)) {
			Rectangle(hdc,
				shape.left,
				shape.top,
				shape.right,
				shape.bottom);
		}

		if (itemTank) {
			if (hp == 4)img->Render(hdc, pos.x, pos.y, elapsedCount + elapsedWay, itemTankImg(6));
			else img->Render(hdc, pos.x, pos.y, elapsedCount + elapsedWay, bigTankFrame);
		}
		else {
			img->Render(hdc, pos.x, pos.y, elapsedCount + elapsedWay, bigTankFrame);
		}
	}
	else {
		if (destructionEffectNum < 5)destructionEffect1->Render(hdc, pos.x, pos.y, destructionEffectNum, 0);
		if (destructionEffectNum == 5) destructionEffect1->Render(hdc, pos.x, pos.y, 3, 0);
		if (destructionEffectNum == 6) destructionEffect1->Render(hdc, pos.x, pos.y, 2, 0);
		if (destructionEffectNum == 7) destructionEffect1->Render(hdc, pos.x, pos.y, 1, 0);
		if (destructionEffectNum >= 8 && !boomItemCheck) pointImage->Render(hdc, pos.x, pos.y, 3, 0);
	}
}

void BigEnemyTank::Release()
{
}

void BigEnemyTank::AutoFire()
{
	attackDelayTime += TimerManager::GetSingleton()->GetDeltaTime();

	if (attackDelayTime > attackDelay)
	{
		ammoManager->Fire(movedir, pos, type, false);
		attackDelay = rand() % 3 + 1;

		attackDelayTime = 0.0f;
	}
}
