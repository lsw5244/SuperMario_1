#include "ClearScene.h"
#include "Image.h"
#include "CommonFunction.h"
#include "MacroCollection.h"

HRESULT ClearScene::Init()
{
	SetWindowSize(300, 20, GAME_SCENE_WIN_SIZE_X, GAME_SCENE_WIN_SIZE_Y);

	background = ImageManager::GetInstance()->FindImage("Image/Clear/ClearSceneImage.bmp");

	elapsedTime = 0.0f;
	return S_OK;
}

void ClearScene::Update()
{
	elapsedTime += DELETA_TIME;

	if (elapsedTime > changeSceneDelay)
	{
		SceneManager::GetInstance()->ChangeScene("TitleScene");
	}
}

void ClearScene::Render(HDC hdc)
{
	background->Render(hdc);
}

void ClearScene::Release()
{
}
