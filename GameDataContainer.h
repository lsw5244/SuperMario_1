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
	int globalPos			= 0;
	AmmoManager* ammoManger = nullptr;
	ItemManager* itemManager = nullptr;

public:
	TILE(*map)[MAP_WIDTH] = {};

	void Init();
	void Release();

	void SetPlayer(PlayerCharacter* player) { this->player = player; }
	PlayerCharacter* GetPlayer() { return this->player;	}

	void SetMap(TILE(*map)[MAP_WIDTH]) { this->map = map; }

	void SetGlobalPos(int pos) { this->globalPos = pos;	}
	int GetGlobalPos() { return this->globalPos; }

	void SetAmmoManager(AmmoManager* ammoManager) { this->ammoManger = ammoManager;	}
	AmmoManager* GetAmmoManager() {	return this->ammoManger; }

	void SetItemManager(ItemManager* itemManager) {	this->itemManager = itemManager; }
	ItemManager* GetItemManager() {	return itemManager;	}
};

