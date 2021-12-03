#pragma once
#include "Config.h"
#include "GameObject.h"
#include <vector>
using namespace std;
class PlayerTank;
class EnemyTanks;
class AmmoManager;
class EnemyTankFactory
{
private:
protected:

public:
	virtual EnemyTanks* CreateEnemyTank() = 0;
	EnemyTankFactory() {}
	~EnemyTankFactory();
};

class NormalTankFactory : public EnemyTankFactory
{
private:
	virtual EnemyTanks* CreateEnemyTank() override;
public:
	NormalTankFactory() {}
	~NormalTankFactory();
};

class FastMoveTankFactory : public EnemyTankFactory
{
private:
	virtual EnemyTanks* CreateEnemyTank() override;
public:
	FastMoveTankFactory() {}
	~FastMoveTankFactory();
};

class FastShootTankFactory : public EnemyTankFactory
{
private:
	virtual EnemyTanks* CreateEnemyTank() override;
public:
	FastShootTankFactory() {}
	~FastShootTankFactory();
};

class BigTankFactory : public EnemyTankFactory
{
private:
	virtual EnemyTanks* CreateEnemyTank() override;
public:
	BigTankFactory() {}
	~BigTankFactory();
};

