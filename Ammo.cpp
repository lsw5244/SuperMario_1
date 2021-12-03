#include "Ammo.h"
#include "Image.h"
#include "PlayerTank.h"
#include "CommonFunction.h"
#include "EnemyTanks.h"
HRESULT Ammo::Init()
{

	boomEffect = ImageManager::GetSingleton()->FindImage("Image/Effect/Boom_Effect.bmp");
	isAlive;
	//dir = MoveDir::Right;
	renderBoomEffect = false;
	showCollider = false;

	sec = 0.0f;

	pos = { -10, -10 };

	moveSpeed = 100.0f;

	bodySize = 4;

	shape.left = pos.x - bodySize / 2;
	shape.right = shape.left + bodySize;
	shape.top = pos.y - bodySize / 2;
	shape.bottom = shape.top + bodySize;

	SetRect(&gameSceneRect, 16, 8, 224, 216);

	hitTile1 = nullptr;
	hitTile2 = nullptr;

	//isHit = false;
	boomEffectFrameX = 0;

	canDestroyIronWall = false;
	return S_OK;
}

void Ammo::Update()
{
	if (type == TankType::Enemy && isAlive == true)
	{
		for (int i = 0; i < 2; i++)
		{
			if (playerAmmos[i]->GetIsAlive() == true && CollisionEnter(playerAmmos[i]->GetRect(), shape))
			{
				playerAmmos[i]->EraseAmmo();

				EraseAmmo();
			}
		}
	}

	if (CollisionEnter(*(playerTank->GetRect()), shape) && type != TankType::Player)
	{
		playerTank->SetIsDead(true);
		DestroyAmmo();
	}

	for (vector<EnemyTanks*>::iterator it = vecEnemys.begin(); it != vecEnemys.end(); it++)
	{
		if (CollisionEnter((*it)->GetRect(), shape) && type != TankType::Enemy && isAlive == true && (*it)->GetHp() > 0)
		{
			DestroyAmmo();
			(*it)->isHit();
			break;
		}
	}

	if (isAlive == true)
	{
		AmmoHitCheck();
	}

	shape.left = pos.x - bodySize / 2;
	shape.right = shape.left + bodySize;
	shape.top = pos.y - bodySize / 2;
	shape.bottom = shape.top + bodySize;

	if (!(CollisionEnter(gameSceneRect, shape)) && isAlive == true)
	{
		DestroyAmmo();
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('P'))
	{
		showCollider = showCollider ? false : true;
	}

	if (isAlive == false)
	{
		return;
	}

	switch (dir)
	{
	case MoveDir::Left:
		pos.x -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();;
		break;
	case MoveDir::Right:
		pos.x += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();;
		break;
	case MoveDir::Up:
		pos.y -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
		break;
	case MoveDir::Down:
		pos.y += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();;
		break;
	}
}

void Ammo::Render(HDC hdc)
{
	if (renderBoomEffect == true && isAlive == false)
	{
		boomEffect->Render(hdc, pos.x, pos.y, boomEffectFrameX, boomEffect->GetCurrFrameY());
		sec += TimerManager::GetSingleton()->GetDeltaTime();
		if (sec > 0.03f)
		{
			sec = 0.0f;
			boomEffectFrameX++;
			if (boomEffectFrameX > 2)
			{
				renderBoomEffect = false;
				boomEffectFrameX = 0;
				pos = { -10, -10 };
				if (isFastAmmo == true)
				{
					moveSpeed /= 2;
					isFastAmmo = false;
				}
			}
		}
	}

	if (isAlive == false)
	{
		return;
	}

	img->Render(hdc, pos.x, pos.y);

	if (showCollider == true)
	{
		Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);
	}
}

void Ammo::Release()
{

}

void Ammo::Fire(MoveDir dir, POINTFLOAT pos, bool isFastAmmo)
{
	if (isFastAmmo == true)
	{
		moveSpeed *= 2;
		this->isFastAmmo = true;
	}
	isAlive = true;
	this->pos = pos;
	switch (dir)
	{
	case MoveDir::Left:
		img = ImageManager::GetSingleton()->FindImage("Image/Bullet/Missile_Left.bmp");
		this->dir = dir;
		break;
	case MoveDir::Right:
		img = ImageManager::GetSingleton()->FindImage("Image/Bullet/Missile_Right.bmp");
		this->dir = dir;
		break;
	case MoveDir::Up:
		img = ImageManager::GetSingleton()->FindImage("Image/Bullet/Missile_Up.bmp");
		this->dir = dir;
		break;
	case MoveDir::Down:
		img = ImageManager::GetSingleton()->FindImage("Image/Bullet/Missile_Down.bmp");
		this->dir = dir;
		break;
	}
}

void Ammo::DestroyAmmo()
{
	isAlive = false;
	renderBoomEffect = true;
}

void Ammo::EraseAmmo()
{
	isAlive = false;
	pos = { -10, -10 };
	if (isFastAmmo == true)
	{
		moveSpeed /= 2;
		isFastAmmo = false;
	}
}

void Ammo::AmmoHitCheck()
{
	for (int i = GetPosCount(pos.y, -2, false); i < GetPosCount(pos.y, 2, false); i++)
	{
		for (int j = GetPosCount(pos.x, -2, true); j < GetPosCount(pos.x, 2, true); j++)
		{
			if (CollisionEnter(tileInfo[i][j].selectRc, shape))
			{
				// base hit
				if (tileInfo[i][j].terrain == Terrain::Base)
				{
					DestroyAmmo();
					DestroyBase();
					return;
				}
				if (CollisionEnter(tileInfo[i + 1][j].selectRc, shape) &&
					tileInfo[i + 1][j].terrain == Terrain::Base ||
					CollisionEnter(tileInfo[i][j + 1].selectRc, shape) &&
					tileInfo[i][j + 1].terrain == Terrain::Base)
				{
					DestroyAmmo();
					DestroyBase();
					return;
				}

				// brick hit
				if (tileInfo[i][j].terrain == Terrain::Brick)
				{
					hitTile1 = &tileInfo[i][j];					
					// brick and iron
					if (CollisionEnter(tileInfo[i + 1][j].selectRc, shape) &&
						tileInfo[i + 1][j].terrain == Terrain::IronBrick)
					{
						hitTile2 = &tileInfo[i + 1][j];
						if (canDestroyIronWall == true)
						{
							PowerAmmoDestroyWall(hitTile1, hitTile2);
						}
						else
						{
							IronWallHitDestroyWall(hitTile1);
						}
					}
					// brick and iron
					else if (CollisionEnter(tileInfo[i][j + 1].selectRc, shape) &&
							tileInfo[i][j + 1].terrain == Terrain::IronBrick)
					{
						hitTile2 = &tileInfo[i][j + 1];
						if (canDestroyIronWall == true)
						{
							PowerAmmoDestroyWall(hitTile1, hitTile2);
						}
						else
						{
							IronWallHitDestroyWall(hitTile1);
						}		
					}
					// brick and brick
					else if (CollisionEnter(tileInfo[i + 1][j].selectRc, shape) &&
						tileInfo[i + 1][j].terrain == Terrain::Brick)
					{
						hitTile2 = &tileInfo[i + 1][j];
						if (canDestroyIronWall == true)
						{
							PowerAmmoDestroyWall(hitTile1, hitTile2);
						}
						else
						{
							DestroyWall(hitTile1, hitTile2);
						}
					}
					// brick and brick
					else if (CollisionEnter(tileInfo[i][j + 1].selectRc, shape) &&
						tileInfo[i][j + 1].terrain == Terrain::Brick)
					{
						hitTile2 = &tileInfo[i][j + 1];
						if (canDestroyIronWall == true)
						{
							PowerAmmoDestroyWall(hitTile1, hitTile2);
						}
						else
						{
							DestroyWall(hitTile1, hitTile2);
						}
					}
					// only brick
					else
					{
						if (canDestroyIronWall == true)
						{
							PowerAmmoDestroyWall(hitTile1);
						}
						else
						{
							DestroyWall(hitTile1);
						}
					}
					return;
				}

				// iron hit
				if (tileInfo[i][j].terrain == Terrain::IronBrick)
				{
					hitTile1 = &tileInfo[i][j];

					// iron and iron
					if (CollisionEnter(tileInfo[i + 1][j].selectRc, shape) &&
							tileInfo[i + 1][j].terrain == Terrain::IronBrick)
					{
						if (canDestroyIronWall == true)
						{
							hitTile2 = &tileInfo[i + 1][j];
							PowerAmmoDestroyWall(hitTile1, hitTile2);
						}
					}
					// iron and iron
					else if (CollisionEnter(tileInfo[i][j + 1].selectRc, shape) &&
							tileInfo[i][j + 1].terrain == Terrain::IronBrick)
					{
						if (canDestroyIronWall == true)
						{
							hitTile2 = &tileInfo[i][j + 1];
							PowerAmmoDestroyWall(hitTile1, hitTile2);
						}
					}
					else
					{

					}

					// iron and brick
					if (CollisionEnter(tileInfo[i + 1][j].selectRc, shape) &&
						tileInfo[i + 1][j].terrain == Terrain::Brick)
					{
						hitTile2 = &tileInfo[i + 1][j];
						if (canDestroyIronWall == true)
						{
							PowerAmmoDestroyWall(hitTile1, hitTile2);

						}
						else
						{
							IronWallHitDestroyWall(hitTile2);
						}
					}
					// iron and brick
					else if (CollisionEnter(tileInfo[i][j + 1].selectRc, shape) &&
						tileInfo[i][j + 1].terrain == Terrain::Brick)
					{
						hitTile2 = &tileInfo[i][j + 1];
						if (canDestroyIronWall == true)
						{
							PowerAmmoDestroyWall(hitTile1, hitTile2);

						}
						else
						{
							IronWallHitDestroyWall(hitTile2);
						}
					}
					else
					{
						if (canDestroyIronWall == true)
						{
							PowerAmmoDestroyWall(hitTile1);
						}
						else
						{
							DestroyAmmo();
						}
					}
					return;
				}

			}
		}
	}

}


void Ammo::DestroyWall(TILE_INFO* tileInfo)
{
	//tileInfo->isDes[0][0] = false;
	if (isAlive == false)	return;

	DestroyAmmo();

	switch (dir)
	{
	case MoveDir::Down:
		if (tileInfo->isDes[0][0] == false && tileInfo->isDes[0][1] == false)
		{
			tileInfo->isDes[1][0] = false;
			tileInfo->isDes[1][1] = false;
		}
		else
		{
			tileInfo->isDes[0][0] = false;
			tileInfo->isDes[0][1] = false;
		}
		break;

	case MoveDir::Up:
		if (tileInfo->isDes[1][0] == false && tileInfo->isDes[1][1] == false)
		{
			tileInfo->isDes[0][0] = false;
			tileInfo->isDes[0][1] = false;
		}
		else
		{
			tileInfo->isDes[1][0] = false;
			tileInfo->isDes[1][1] = false;
		}
		break;

	case MoveDir::Left:
		if (tileInfo->isDes[0][1] == false && tileInfo->isDes[1][1] == false)
		{
			tileInfo->isDes[0][0] = false;
			tileInfo->isDes[1][0] = false;
		}
		else
		{
			tileInfo->isDes[0][1] = false;
			tileInfo->isDes[1][1] = false;
		}
		break;

	case MoveDir::Right:
		if (tileInfo->isDes[0][0] == false && tileInfo->isDes[1][0] == false)
		{
			tileInfo->isDes[0][1] = false;
			tileInfo->isDes[1][1] = false;
		}
		else
		{
			tileInfo->isDes[0][0] = false;
			tileInfo->isDes[1][0] = false;
		}
		break;
	}

	hitTile1 = nullptr;
	hitTile2 = nullptr;
}

void Ammo::DestroyWall(TILE_INFO* tileInfo1, TILE_INFO* tileinfo2)
{
	if (isAlive == false)	return;

	DestroyAmmo();

	switch (dir)
	{
	case MoveDir::Down:
		if (tileInfo1->isDes[0][0] == false &&
			tileInfo1->isDes[0][1] == false &&
			tileinfo2->isDes[0][0] == false &&
			tileinfo2->isDes[0][1] == false)
		{
			tileInfo1->isDes[1][0] = false;
			tileInfo1->isDes[1][1] = false;
			tileinfo2->isDes[1][0] = false;
			tileinfo2->isDes[1][1] = false;
		}
		else
		{
			tileInfo1->isDes[0][0] = false;
			tileInfo1->isDes[0][1] = false;
			tileinfo2->isDes[0][0] = false;
			tileinfo2->isDes[0][1] = false;
		}
		break;

	case MoveDir::Up:
		if (tileInfo1->isDes[1][0] == false &&
			tileInfo1->isDes[1][1] == false &&
			tileinfo2->isDes[1][0] == false &&
			tileinfo2->isDes[1][1] == false)
		{
			tileInfo1->isDes[0][0] = false;
			tileInfo1->isDes[0][1] = false;
			tileinfo2->isDes[0][0] = false;
			tileinfo2->isDes[0][1] = false;
		}
		else
		{
			tileInfo1->isDes[1][0] = false;
			tileInfo1->isDes[1][1] = false;
			tileinfo2->isDes[1][0] = false;
			tileinfo2->isDes[1][1] = false;
		}
		break;

	case MoveDir::Left:
		if (tileInfo1->isDes[0][1] == false &&
			tileInfo1->isDes[1][1] == false &&
			tileinfo2->isDes[0][1] == false &&
			tileinfo2->isDes[1][1] == false)
		{
			tileInfo1->isDes[0][0] = false;
			tileInfo1->isDes[1][0] = false;
			tileinfo2->isDes[0][0] = false;
			tileinfo2->isDes[1][0] = false;
		}
		else
		{
			tileInfo1->isDes[0][1] = false;
			tileInfo1->isDes[1][1] = false;
			tileinfo2->isDes[0][1] = false;
			tileinfo2->isDes[1][1] = false;
		}
		break;

	case MoveDir::Right:
		if (tileInfo1->isDes[0][0] == false &&
			tileInfo1->isDes[1][0] == false &&
			tileinfo2->isDes[0][0] == false &&
			tileinfo2->isDes[1][0] == false)
		{
			tileInfo1->isDes[0][1] = false;
			tileInfo1->isDes[1][1] = false;
			tileinfo2->isDes[0][1] = false;
			tileinfo2->isDes[1][1] = false;
		}
		else
		{
			tileInfo1->isDes[0][0] = false;
			tileInfo1->isDes[1][0] = false;
			tileinfo2->isDes[0][0] = false;
			tileinfo2->isDes[1][0] = false;
		}
		break;
	}

	hitTile1 = nullptr;
	hitTile2 = nullptr;
}

void Ammo::PowerAmmoDestroyWall(TILE_INFO* tileInfo1, TILE_INFO* tileinfo2)
{
	if (isAlive == false)	return;

	DestroyAmmo();

	switch (dir)
	{
	case MoveDir::Down:
			tileInfo1->isDes[1][0] = false;
			tileInfo1->isDes[1][1] = false;
			tileinfo2->isDes[1][0] = false;
			tileinfo2->isDes[1][1] = false;

			tileInfo1->isDes[0][0] = false;
			tileInfo1->isDes[0][1] = false;
			tileinfo2->isDes[0][0] = false;
			tileinfo2->isDes[0][1] = false;
		
		break;

	case MoveDir::Up:

			tileInfo1->isDes[0][0] = false;
			tileInfo1->isDes[0][1] = false;
			tileinfo2->isDes[0][0] = false;
			tileinfo2->isDes[0][1] = false;

			tileInfo1->isDes[1][0] = false;
			tileInfo1->isDes[1][1] = false;
			tileinfo2->isDes[1][0] = false;
			tileinfo2->isDes[1][1] = false;
		
		break;

	case MoveDir::Left:

			tileInfo1->isDes[0][0] = false;
			tileInfo1->isDes[1][0] = false;
			tileinfo2->isDes[0][0] = false;
			tileinfo2->isDes[1][0] = false;

			tileInfo1->isDes[0][1] = false;
			tileInfo1->isDes[1][1] = false;
			tileinfo2->isDes[0][1] = false;
			tileinfo2->isDes[1][1] = false;
		
		break;

	case MoveDir::Right:

			tileInfo1->isDes[0][1] = false;
			tileInfo1->isDes[1][1] = false;
			tileinfo2->isDes[0][1] = false;
			tileinfo2->isDes[1][1] = false;

			tileInfo1->isDes[0][0] = false;
			tileInfo1->isDes[1][0] = false;
			tileinfo2->isDes[0][0] = false;
			tileinfo2->isDes[1][0] = false;
		break;
	}

	hitTile1 = nullptr;
	hitTile2 = nullptr;
}

void Ammo::PowerAmmoDestroyWall(TILE_INFO* tileInfo1)
{
	if (isAlive == false)	return;

	DestroyAmmo();

	switch (dir)
	{
	case MoveDir::Down:
		tileInfo1->isDes[1][0] = false;
		tileInfo1->isDes[1][1] = false;

		tileInfo1->isDes[0][0] = false;
		tileInfo1->isDes[0][1] = false;

		break;

	case MoveDir::Up:
		tileInfo1->isDes[0][0] = false;
		tileInfo1->isDes[0][1] = false;

		tileInfo1->isDes[1][0] = false;
		tileInfo1->isDes[1][1] = false;
		break;

	case MoveDir::Left:
		tileInfo1->isDes[0][0] = false;
		tileInfo1->isDes[1][0] = false;

		tileInfo1->isDes[0][1] = false;
		tileInfo1->isDes[1][1] = false;

		break;

	case MoveDir::Right:
		tileInfo1->isDes[0][1] = false;
		tileInfo1->isDes[1][1] = false;

		tileInfo1->isDes[0][0] = false;
		tileInfo1->isDes[1][0] = false;

		break;
	}

	hitTile1 = nullptr;
	hitTile2 = nullptr;
}

void Ammo::IronWallHitDestroyWall(TILE_INFO* tileInfo)
{
	if (isAlive == false)	return;

	DestroyAmmo();

	switch (dir)
	{
	case MoveDir::Left:
		tileInfo->isDes[0][1] = false;
		tileInfo->isDes[1][1] = false;
		break;
	case MoveDir::Right:
		tileInfo->isDes[0][0] = false;
		tileInfo->isDes[1][0] = false;
		break;
	case MoveDir::Up:
		tileInfo->isDes[1][0] = false;
		tileInfo->isDes[1][1] = false;
		break;
	case MoveDir::Down:
		tileInfo->isDes[0][0] = false;
		tileInfo->isDes[0][1] = false;
		break;
	}

	hitTile1 = nullptr;
	hitTile2 = nullptr;
}

void Ammo::DestroyBase()
{
	baseStartPoint = { 24, 12 };
	tileInfo[baseStartPoint.x][baseStartPoint.y].terrain = Terrain::BaseDes; // 각 1/4 칸
	tileInfo[baseStartPoint.x][baseStartPoint.y].frameX[0] += 4;
	tileInfo[baseStartPoint.x][baseStartPoint.y].frameX[1] += 4;
	tileInfo[baseStartPoint.x + 1][baseStartPoint.y].terrain = Terrain::BaseDes;
	tileInfo[baseStartPoint.x + 1][baseStartPoint.y].frameX[0] += 4;
	tileInfo[baseStartPoint.x + 1][baseStartPoint.y].frameX[1] += 4;

	tileInfo[baseStartPoint.x][baseStartPoint.y + 1].terrain = Terrain::BaseDes;
	tileInfo[baseStartPoint.x][baseStartPoint.y + 1].frameX[0] += 4;
	tileInfo[baseStartPoint.x][baseStartPoint.y + 1].frameX[1] += 4;
	tileInfo[baseStartPoint.x + 1][baseStartPoint.y + 1].terrain = Terrain::BaseDes;
	tileInfo[baseStartPoint.x + 1][baseStartPoint.y + 1].frameX[0] += 4;
	tileInfo[baseStartPoint.x + 1][baseStartPoint.y + 1].frameX[1] += 4;

}

bool Ammo::CollisionEnter(RECT rc1, RECT rc2)
{
	if (rc1.left > rc2.right)	return false;
	if (rc1.right < rc2.left)	return false;
	if (rc1.top > rc2.bottom)	return false;
	if (rc1.bottom < rc2.top)	return false;

	return true;
}
