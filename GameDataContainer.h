#pragma once
#include "Singleton.h"
#include "PlayerCharacter.h"
#include "StructCollection.h"
#include "MacroCollection.h"

class GameDataContainer : public Singleton<GameDataContainer>
{
private:
	PlayerCharacter* player = nullptr;
	int globalPos			= 0;

public:
	TILE(*map)[MAP_WIDTH] = {};

	void Init();
	void Release();

	void SetPlayer(PlayerCharacter* player)
	{
		this->player = player;
	}
	PlayerCharacter* GetPlayer()
	{
		return this->player;
	}
	//void SetTileInfo(TILE_INFO(*info)[TILE_COUNT]) { this->tileInfo = info; }

	void SetMap(TILE(*map)[MAP_WIDTH])
	{
		this->map = map;
	}
	//TILE/*[MAP_HEIGHT][MAP_WIDTH]*/ GetMap()
	//{
	//	return map;
	//}

	void SetGlobalPos(int pos)
	{
		this->globalPos = pos;
	}

	int GetGlobalPos()
	{
		return this->globalPos;
	}
};

