#include "MainGame.h"
#include "Image.h"
#include "ImageManager.h"
#include "GameDataContainer.h"
#include "GlobalVariableCollection.h"
#include "MacroCollection.h"

HRESULT MainGame::Init()
{
	KeyManager::GetInstance()->Init();
	ImageManager::GetInstance()->Init();

	// 이미지 초기화
	TimerManager::GetInstance()->Init();
	SceneManager::GetInstance()->Init();

	//SceneManager::GetSingleton()->AddLoadingScene("LoadingScene", new LoadingScene());

	SceneManager::GetInstance()->ChangeScene("TempScene");

	//srand((unsigned int) time(nullptr));

	//clickedMousePosX = 0; 
	//clickedMousePosY = 0; 

	// 백버퍼
	backBuffer = new Image;

	backBuffer->Init("Image/mapImage.bmp",800, 800);

	return S_OK;
}

void MainGame::Update()
{
	TimerManager::GetInstance()->Update();

	SceneManager::GetInstance()->Update();

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HDC hBackBufferDC = backBuffer->GetMemDC();

	PatBlt(hBackBufferDC, 0, 0, backBuffer->GetWidth(), backBuffer->GetHeight(), WHITENESS);

	SceneManager::GetInstance()->Render(hBackBufferDC);

	backBuffer->Render(hdc);
}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);

	TimerManager::GetInstance()->Release();

	ImageManager::GetInstance()->Release();

	KeyManager::GetInstance()->Release();

	SceneManager::GetInstance()->Release();

	GameDataContainer::GetInstance()->Release();
}


LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		break;
	case WM_LBUTTONDOWN:
		//clickedMousePosX = LOWORD(lParam);
		//clickedMousePosY = HIWORD(lParam);
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
