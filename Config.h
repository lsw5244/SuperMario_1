#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <map>
#include <iostream>
#include <string>

using namespace std;

#pragma comment(lib, "winmm.lib")

#define WIN_START_POS_X	400
#define WIN_START_POS_Y	100

#define WIN_SIZE_X	256//Ÿ�� �� �� �̿� �� 800
#define WIN_SIZE_Y	240//Ÿ�� �� �� �̿� �� 800

#define GAME_SCENE_WIN_SIZE_X WIN_SIZE_X * 3
#define GAME_SCENE_WIN_SIZE_Y WIN_SIZE_Y * 3
						  
#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }
#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }

typedef struct ArgumentFuncPtr
{
	string sceneName;
	string loadingSceneName;
} ARGUMENT_PTR, *LPARGUMENT_PTR;

#include "TimerManager.h"
#include "ImageManager.h"
#include "KeyManager.h"
#include "SceneManager.h"

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;
//extern int windowX;
//extern int windowY;

/*------------------*/

#define MAP_WIDTH_PER_PAGE 50

#define MAP_WIDTH 211		// 211 ĭ
#define MAP_HEIGHT 15		// 15 ĭ

#define TILE_SPRITE_WIDTH 11
#define TILE_SPRITE_HEIGHT 13

#define TILE_SIZE 16		// ���� ���� 16�ȼ�

enum class MoveDirection
{
	Left, Right, End
};

enum class BlockType
{
	Brick, CanDestroyBrick, ItemBlock, CoinBlock, StarBlock, HiddenCoinBlcok, HiddenStarBlock,// ���� �� �ִ� ��
	Coin,																																// ������ ���� ������ ��
	Background, FlagEnd,																										// ����, �� �� ��� ��
	Flag,  FlagPole, FlagTop,																									//���(������ ���� Ŭ����)
	LateRenderBlock																												// �÷��̾� ���� �� �����Ǵ� ��
};

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