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

	void AnimationFrameChanger();	
	void AnimationFrameChanger(int frameX, int frameY);	// �ִϸ��̼� ���� ������ �� ���

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~TempScene() = default;

};

