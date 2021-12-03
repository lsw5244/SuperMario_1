#pragma once
#include "Config.h"
#include "GameEntity.h"

class ButtonFunction;
class Button;
class Image;
class TitleScene : public GameEntity
{
private:
	//Button* btnGotoBattle;
	//Button* btnQuitProgram;

	//LPARGUMENT_PTR arg;

	Image* backGround;
	Image* titleBackGround;
	POINT titlePos;

	Image* plyaerSelect;
	POINT selectPos;
	int selectFrame;
	bool Player_1p;

	float time;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~TitleScene() = default;
};

