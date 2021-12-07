#pragma once
#include "HeaderCollection.h"
#include "EnumClassCollection.h"

typedef struct ArgumentFuncPtr
{
	string sceneName;
	string loadingSceneName;
} ARGUMENT_PTR, * LPARGUMENT_PTR;

struct SampleTile
{
	RECT rc;
	int frameX;
	int frameY;
	int animationFrameX;
	int maxAnimationFrameX;
	int itemCount;
	bool isCollider;
};

struct TILE
{
	BlockType type;
	RECT rc;
	int frameX;
	int frameY;
	int animationFrameX;
	int maxAnimationFrameX;
	int itemCount;
	bool isCollider;
};