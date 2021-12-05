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
#define WIN_SIZE_X	800 //240(게임으로 할 때 사용)// 16 * 16
#define WIN_SIZE_Y	800 //240			// 16 * 14

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
extern int windowX;
extern int windowY;

/*------------------*/

#define MAP_WIDTH_PER_PAGE 50

#define MAP_WIDTH 211
#define MAP_HEIGHT 15

#define TILE_SPRITE_WIDTH 11
#define TILE_SPRITE_HEIGHT 13

#define TILE_SIZE 16		// 가로 세로 16픽셀

enum class MoveDirection
{
	Left, Right, End
};

enum class BlockType
{
	Brick, CanDestroyBrick, ItemBlock, CoinBlock, StarBlock, HiddenCoinBlcok, HiddenStarBlock,// 밟을 수 있는 블럭
	Coin,																																// 닿으면 점수 오르는 블럭
	Background, FlagEnd,																										// 구름, 산 등 배경 블럭
	Flag,  FlagPole, FlagTop,																									//깃발(닿으면 게임 클리어)
	LateRenderBlock																												// 플레이어 랜더 후 랜더되는 블럭
};

struct SampleTile
{
	RECT rc;
	int frameX;
	int frameY;
};

struct TILE
{
	BlockType type;
	RECT rc;
	int frameX;
	int frameY;
};