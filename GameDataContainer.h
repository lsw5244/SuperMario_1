#pragma once
#include "Singleton.h"
#include "PlayerCharacter.h"
#include "Config.h"
class GameDataContainer : public Singleton<GameDataContainer>
{
private:
	PlayerCharacter* player = nullptr;

	TILE* map				= nullptr;

public:
	void SetPlayer(PlayerCharacter* player)
	{
		this->player = player;
	}
	PlayerCharacter* GetPlayer()
	{
		return this->player;
	}

	void SetMap(TILE* map)
	{
		this->map = map;
	}
	TILE* GetMap()
	{
		return map;
	}
};

