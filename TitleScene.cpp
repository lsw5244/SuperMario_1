#include "TitleScene.h"
#include "Image.h"
#include "CommonFunction.h"
#include "MacroCollection.h"
#include "Input.h"

HRESULT TitleScene::Init()
{
	SetWindowSize(300, 20, GAME_SCENE_WIN_SIZE_X, GAME_SCENE_WIN_SIZE_Y);

	backGround = ImageManager::GetInstance()->FindImage("Image/Title/TitleImage.bmp");
	selectImage = ImageManager::GetInstance()->FindImage("Image/Title/SelectMushroom.bmp");

	selectImagePos = { 76, 148 }; // À§ ÁÂÇ¥
	selectImagePos = { 76, 164 }; // ¾Æ·¡ ÁÂÇ¥

	return S_OK;
}

void TitleScene::Update()
{
}

void TitleScene::Render(HDC hdc)
{
	backGround->Render(hdc);
	selectImage->Render(hdc, selectImagePos.x, selectImagePos.y);
}

void TitleScene::Release()
{
}
