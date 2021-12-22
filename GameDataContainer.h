#pragma once
#include "Singleton.h"
#include "PlayerCharacter.h"
#include "AmmoManager.h"
#include "StructCollection.h"
#include "MacroCollection.h"
#include "ItemManager.h"

class GameDataContainer : public Singleton<GameDataContainer>
{
private:
	PlayerCharacter* player = nullptr;
	float globalPos			= 0.0f;
	AmmoManager* ammoManger = nullptr;
	ItemManager* itemManager = nullptr;
	TILE(*map)[MAP_WIDTH] = {};

public:
	//TILE map[MAP_HEIGHT][MAP_WIDTH] = {};

	void Init();
	void Release();

	void SetPlayer(PlayerCharacter* player) { this->player = player; }
	PlayerCharacter* GetPlayer() { return this->player;	}

	void SetMap(TILE(*map)[MAP_WIDTH]) { this->map = map; }
	auto GetMap() { return map; }
	//TILE** GetMap() { return map; }

	void SetGlobalPos(float pos) { this->globalPos = pos;	}
	float GetGlobalPos() { return this->globalPos; }

	void SetAmmoManager(AmmoManager* ammoManager) { this->ammoManger = ammoManager;	}
	AmmoManager* GetAmmoManager() {	return this->ammoManger; }

	void SetItemManager(ItemManager* itemManager) {	this->itemManager = itemManager; }
	ItemManager* GetItemManager() {	return itemManager;	}
};

