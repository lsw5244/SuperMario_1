#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "Physics.h"
#include "Gunba.h"
#include "PlayerCharacter.h"

class Image;
//class Gunba;
class TempScene : public GameEntity
{
private:
	PlayerCharacter mario;
	Gunba mushroom;
	TILE map[MAP_HEIGHT][MAP_WIDTH] = {};
	Image* mapSpriteImg = {};

	void AnimationFrameChanger();	
	void AnimationFrameChanger(int frameX, int frameY);	// 애니메이션 직접 변경할 때 사용

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~TempScene() = default;

	void Load(int loadIndex = 0);

};

