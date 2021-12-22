#pragma once

#define WIN_START_POS_X	400
#define WIN_START_POS_Y	100

#define WIN_SIZE_X	256//Ÿ�� �� �� �̿� �� 800
#define WIN_SIZE_Y	240//Ÿ�� �� �� �̿� �� 800

#define GAME_SCENE_WIN_SIZE_X WIN_SIZE_X * 3
#define GAME_SCENE_WIN_SIZE_Y WIN_SIZE_Y * 3

#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }
#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }

#define MAP_WIDTH_PER_PAGE 50

#define MAP_WIDTH 211		// 211 ĭ
#define MAP_HEIGHT 15		// 15 ĭ

#define TILE_SPRITE_WIDTH 11
#define TILE_SPRITE_HEIGHT 13

#define TILE_SIZE 16		// ���� ���� 16�ȼ�

#define INGAME_RENDER_TILE_WIDHT_COUNT 16

#define DELETA_TIME TimerManager::GetInstance()->GetDeltaTime()
#define TILE_DATA GameDataContainer::GetInstance()->GetMap()
#define GLOBAL_POS GameDataContainer::GetInstance()->GetGlobalPos()
#define PLAYER GameDataContainer::GetInstance()->GetPlayer()
#define AMMO_MANAGER GameDataContainer::GetInstance()->GetAmmoManager()
#define ITEM_MANAGER GameDataContainer::GetInstance()->GetItemManager()