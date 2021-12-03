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
#define TILEMAPTOOL_SIZE_X	500
#define TILEMAPTOOL_SIZE_Y	300
#define PIXELMAP_SIZE_X	800
#define PIXELMAP_SIZE_Y	600

#define ENEMY_SPAWN_POSX	24
#define ENEMY_SPAWN_POSY	16

#define PI 3.14159265357989
#define PI2 (3.14159265357989 * 2)
#define DEGREE_TO_RADIAN(x)		(x * PI / 180.0f)

#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }
#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }

#define TANK_COLLIDER_DEBUG '8'
#define SUPER_PLAYER_MODE '1'

enum class MoveDir { Left, Right, Up, Down };
enum class TankType { Player, Enemy };
enum class EnemyTankType { Normal, FastMove, QuickFire, Big, iNormal, iFastMove, iQuickFire, iBig, End };

typedef struct ArgumentFuncPtr
{
	string sceneName;
	string loadingSceneName;
} ARGUMENT_PTR, *LPARGUMENT_PTR;

#include "TimerManager.h"
#include "ImageManager.h"
#include "KeyManager.h"
#include "SceneManager.h"

#define TILE_SIZE	(8 / 2)
#define TILE_COUNT	(26)
#define SAMPLE_TILE_COUNT	(11*2)
enum class Terrain {
	Brick, IronBrick, Water, Forest, Soild, Empty,
	Base, BaseDes,
	End
};

typedef struct tagTile
{
	Terrain terrain;	// 타일의 타입
	RECT selectRc;		// 탱크 충돌 범위
	RECT rc[2][2];		// 블럭이 부숴지는 단위
	int frameX[2];		// 출력할 X프레임 
	int frameY[2];		// 출력할 Y프레임
	bool isDes[2][2];	// 블럭의 파괴 유무
} TILE_INFO;

enum class TankInfo { Normal, FastMove, FastShoot, BigTank };

enum class MoveDirection
{
	Left, Right, End
};
extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;
extern int windowX;
extern int windowY;