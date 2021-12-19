#pragma once
#include "GameEntity.h"
class Image;
class Item : public GameEntity
{
public:
	Image* img;

	POINTFLOAT pos = {};
	RECT collider = {};
	bool isDead = false;

	int nowTileIndexX = 0;
	int nowTileIndexY = 0;

	void UpdateCollider();
	bool OnCollisionEnter(RECT plyaerRect, RECT tileRect);
public:

};

