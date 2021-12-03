#include "EnemyTankFactory.h"
#include "NormalEnemyTank.h"
#include "FastMoveEnemyTank.h"
#include "FastShootEnemyTank.h"
#include "BigEnemyTank.h"

EnemyTanks* NormalTankFactory::CreateEnemyTank()
{
	return new NormalEnemyTank;
}

NormalTankFactory::~NormalTankFactory()
{
}

EnemyTanks* FastMoveTankFactory::CreateEnemyTank()
{
	return new FastMoveEnemyTank;
}

FastMoveTankFactory::~FastMoveTankFactory()
{
}

EnemyTanks* FastShootTankFactory::CreateEnemyTank()
{
	return new FastShootEnemyTank;
}

FastShootTankFactory::~FastShootTankFactory()
{
}

EnemyTanks* BigTankFactory::CreateEnemyTank()
{
	return new BigEnemyTank;
}

BigTankFactory::~BigTankFactory()
{
}

EnemyTankFactory::~EnemyTankFactory()
{
}
