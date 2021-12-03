#include "MainGame.h"
#include "Image.h"
#include "ImageManager.h"
#include "TitleScene.h"
#include "BattleScene.h"
#include "TilemapToolScene.h"
#include "TotalScene.h"
#include "ScoreManager.h"
#include "GameDataManager.h"
#include "TempScene.h"
#include "MyTileMapTool.h"
HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	{
		ImageManager::GetSingleton()->AddImage("Image/SamlpTile.bmp", 88, 88, SAMPLE_TILE_COUNT, SAMPLE_TILE_COUNT, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/background.bmp", WIN_SIZE_X, WIN_SIZE_Y);
		ImageManager::GetSingleton()->AddImage("Image/Player/Player3.bmp", 128, 76, 8, 4, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Enemy/Enemy.bmp", 128, 96, 8, 6, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Enemy/Enemy_Item.bmp", 128, 128, 8, 8, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Effect/Spawn_Effect.bmp", 64, 16, 4, 1, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Effect/Boom_Effect.bmp", 48, 16, 3, 1, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Effect/EnemyTankBoom.bmp", 160, 32, 5, 1, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Effect/Shield.bmp", 32, 16, 2, 1, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Bullet/Missile_Down.bmp", 3, 4, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Bullet/Missile_Left.bmp", 4, 3, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Bullet/Missile_Right.bmp", 4, 3, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Bullet/Missile_Up.bmp", 3, 4, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Icon/Icon_Enemy.bmp", 8, 8, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Icon/player1Life.bmp", 16, 16, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Icon/Point.bmp", 80, 16, 5, 1, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Icon/Arrow.bmp", 8, 7, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/item/items.bmp", 96, 16, 6, 1, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Text/Number.bmp", 40, 14, 5, 2, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Text/Number1.bmp", 40, 14, 5, 2, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Text/Stage.bmp", 37, 7, 1, 1, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Text/Number_w.bmp", 40, 14, 5, 2, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Text/HISocre.bmp", 140, 7, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Text/Player1.bmp", 63, 7, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Text/PTS.bmp", 22, 7, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Text/TotalScore.bmp", 110, 10, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Text/ScoreNumber.bmp", 40, 14, 5, 2, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Text/Stage_w.bmp", 37, 7, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/loading.bmp", WIN_SIZE_X, WIN_SIZE_Y);
		ImageManager::GetSingleton()->AddImage("Image/Title/background.bmp", 256, 224);
		ImageManager::GetSingleton()->AddImage("Image/Title/Title.bmp", 256, 224);
		ImageManager::GetSingleton()->AddImage("Image/Title/PlayerSelect.bmp", 30, 15, 2, 1, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Title/BattleGameOver.bmp", 32, 15, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Title/GrayBackGround.bmp", 256, 112, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Title/ScoreGameOver.bmp", 124, 80, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Title/GameClear.bmp", 150, 80, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Enemy/Enemy.bmp", 128, 96, 8, 6, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/SamllRedMario.bmp", 224, 64, 14, 2, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Gunba.bmp", 64, 32, 4, 2, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/mario_overwordTile_real.bmp", 176, 208, 11, 13, true, RGB(255, 0, 255));
	}
	// 이미지 초기화
	TimerManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();

	SceneManager::GetSingleton()->AddScene("TitleScene", new TitleScene());
	SceneManager::GetSingleton()->AddScene("BattleScene", new BattleScene());
	SceneManager::GetSingleton()->AddScene("TilemapToolScene", new TilemapToolScene());
	SceneManager::GetSingleton()->AddScene("TotalScene", new TotalScene());
	SceneManager::GetSingleton()->AddScene("TempScene", new TempScene());
	SceneManager::GetSingleton()->AddScene("MyTileMapTool", new MyTileMapTool());

	//SceneManager::GetSingleton()->AddLoadingScene("LoadingScene", new LoadingScene());

	SceneManager::GetSingleton()->ChangeScene("MyTileMapTool");

	srand((unsigned int) time(nullptr));

	// 타이머 셋팅
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	clickedMousePosX = 0; 
	clickedMousePosY = 0; 

	// 백버퍼
	backBuffer = new Image;
	//int maxSizeX = WIN_SIZE_X > TILEMAPTOOL_SIZE_X ? WIN_SIZE_X : TILEMAPTOOL_SIZE_X;
	//int maxSizeY = WIN_SIZE_Y > TILEMAPTOOL_SIZE_Y ? WIN_SIZE_Y : TILEMAPTOOL_SIZE_Y;

	backBuffer->Init("Image/mapImage.bmp",800, 800);

	return S_OK;
}

void MainGame::Update()
{
	TimerManager::GetSingleton()->Update();

	//if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_TAB))
	//{
	//	SceneManager::GetSingleton()->ChangeScene("TotalScene");
	//}

	SceneManager::GetSingleton()->Update();

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HDC hBackBufferDC = backBuffer->GetMemDC();

	PatBlt(hBackBufferDC, 0, 0, backBuffer->GetWidth(), backBuffer->GetHeight(), WHITENESS);

	SceneManager::GetSingleton()->Render(hBackBufferDC);

	//TimerManager::GetSingleton()->Render(hBackBufferDC);

	backBuffer->Render(hdc);
}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);

	TimerManager::GetSingleton()->Release();
	TimerManager::GetSingleton()->ReleaseSingleton();

	ImageManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->ReleaseSingleton();

	KeyManager::GetSingleton()->Release();
	KeyManager::GetSingleton()->ReleaseSingleton();

	SceneManager::GetSingleton()->Release();
	SceneManager::GetSingleton()->ReleaseSingleton();

	ScoreManager::GetSingleton()->Release();
	ScoreManager::GetSingleton()->ReleaseSingleton();

	GameDataManager::GetSingleton()->Release();
	GameDataManager::GetSingleton()->ReleaseSingleton();

	// 타이머 객체 삭제
	KillTimer(g_hWnd, 0);
}


LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			break;
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		case VK_LEFT:
			break;
		case VK_RIGHT:
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		clickedMousePosX = LOWORD(lParam);
		clickedMousePosY = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
