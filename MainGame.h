#pragma once
#include "Config.h"
#include "GameEntity.h"

// 우리가 구성할 게임 월드
class Image;
class MainGame : public GameEntity
{
private:
	// 타이머
	HANDLE hTimer = {};

	// UI
	char text[128];

	int clickedMousePosX = {};
	int clickedMousePosY = {};

	// 백버퍼
	Image* backBuffer = {};

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;	// 오버로딩
	virtual void Release() override;
	virtual ~MainGame() = default;
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

//int MainGame::clickedMousePosX = 0;