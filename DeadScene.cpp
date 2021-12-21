#include "DeadScene.h"
#include "CommonFunction.h"
#include "MacroCollection.h"
#include "Image.h"

HRESULT DeadScene::Init()
{
	SetWindowSize(300, 20, GAME_SCENE_WIN_SIZE_X, GAME_SCENE_WIN_SIZE_Y);

	background = ImageManager::GetInstance()->FindImage("Image/DeadScene/DeadScene.bmp");

	elapsedTime = 0.0f;
	return S_OK;
}

void DeadScene::Update()
{
	elapsedTime += DELETA_TIME;

	if (elapsedTime > changeSceneDelay)
	{
		SceneManager::GetInstance()->ChangeScene("TempScene");
	}
}

void DeadScene::Render(HDC hdc)
{
	background->Render(hdc);
}

void DeadScene::Release()
{
}
