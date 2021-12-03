#include "FastMoveEnemyTank.h"
#include "AmmoManager.h"
HRESULT FastMoveEnemyTank::Init()
{
	attackDelay = rand() % 3 + 1;
	tankinfo = TankInfo::FastMove;
	if (itemTank) {
		img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy_Item.bmp");
		itemTime = 0.0f;
		itemfraemY = 2;
	} else {
		img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	}
	moveSpeed = 88.8f;
	hp = 1;
	return S_OK;
}

void FastMoveEnemyTank::Update()
{

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
}

void FastMoveEnemyTank::Render(HDC hdc)
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
			img->Render(hdc, pos.x, pos.y, elapsedCount + elapsedWay, itemTankImg(2));
		}
		else {
			img->Render(hdc, pos.x, pos.y, elapsedCount + elapsedWay, 1);
		}
	}
	else {
		if (destructionEffectNum < 5)destructionEffect1->Render(hdc, pos.x, pos.y, destructionEffectNum, 0);
		if (destructionEffectNum == 5) destructionEffect1->Render(hdc, pos.x, pos.y, 3, 0);
		if (destructionEffectNum == 6) destructionEffect1->Render(hdc, pos.x, pos.y, 2, 0);
		if (destructionEffectNum == 7) destructionEffect1->Render(hdc, pos.x, pos.y, 1, 0);
		if (destructionEffectNum >= 8 && !boomItemCheck) pointImage->Render(hdc, pos.x, pos.y, 1, 0);
	}
}

void FastMoveEnemyTank::Release()
{
}

void FastMoveEnemyTank::AutoFire()
{
	attackDelayTime += TimerManager::GetSingleton()->GetDeltaTime();

	if (attackDelayTime > attackDelay)
	{
		ammoManager->Fire(movedir, pos, type, false);

		attackDelay = rand() % 3 + 1;

		attackDelayTime = 0.0f;
	}
}
