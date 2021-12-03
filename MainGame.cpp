#include "MainGame.h"
#include "Image.h"
#include "ImageManager.h"
#include "TempScene.h"
#include "MyTileMapTool.h"
HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	{
		ImageManager::GetSingleton()->AddImage("Image/SamllRedMario.bmp", 224, 64, 14, 2, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/Gunba.bmp", 64, 32, 4, 2, true, RGB(255, 0, 255));
		ImageManager::GetSingleton()->AddImage("Image/mario_overwordTile_real.bmp", 176, 208, 11, 13, true, RGB(255, 0, 255));
	}
	// 이미지 초기화
	TimerManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();

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
