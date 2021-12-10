#pragma once

#define WIN_START_POS_X	400
#define WIN_START_POS_Y	100

#define WIN_SIZE_X	800//256//Å¸ÀÏ ¸Ê Åø ÀÌ¿ë ½Ã 800
#define WIN_SIZE_Y	800//240//Å¸ÀÏ ¸Ê Åø ÀÌ¿ë ½Ã 800

#define GAME_SCENE_WIN_SIZE_X WIN_SIZE_X * 3
#define GAME_SCENE_WIN_SIZE_Y WIN_SIZE_Y * 3

#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }
#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }

#define MAP_WIDTH_PER_PAGE 50

#define MAP_WIDTH 211		// 211 Ä­
#define MAP_HEIGHT 15		// 15 Ä­

#define TILE_SPRITE_WIDTH 11
#define TILE_SPRITE_HEIGHT 13

#define TILE_SIZE 16		// °¡·Î ¼¼·Î 16ÇÈ¼¿

#define DELTA_TIME TimerManager::GetInstance()->GetDeltaTime()
#define TILE_DATA GameDataContainer::GetInstance()->map
#define GLOBAL_POS GameDataContainer::GetInstance()->GetGlobalPos()
#define PLAYER GameDataContainer::GetInstance()->GetPlayer()