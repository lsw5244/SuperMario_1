#pragma once
#include "GameEntity.h"
class Image;
class Item : public GameEntity
{
public:
	Image* img;

	POINTFLOAT pos = {};
	RECT collider = {};

	bool isSpawning = false;
	bool isDead = false;

	int nowTileIndexX = 0;
	int nowTileIndexY = 0;

	float spawnSpeed = 30.0f;
	float spawnMoveDistance = 0.0f;

	void Spawn(POINTFLOAT pos);
	void SpawnAnimation();

	void UpdateCollider();
	void Destroy();

	bool CollideWithPlayer();
};

