#include "TempScene.h"
#include "CommonFunction.h"
#include "Image.h"

HRESULT TempScene::Init()
{
    //SetWindowSize(300, 20, WIN_SIZE_X, WIN_SIZE_Y);
    SetWindowSize(300, 20, 800, 800);

    //pos.x = WIN_SIZE_X / 2;
    //pos.y = WIN_SIZE_Y / 2;

    mario.SetPos({ WIN_SIZE_X / 2, WIN_SIZE_Y / 2 });
    mushroom.SetPos({ WIN_SIZE_X / 2, WIN_SIZE_Y / 2 });

    return S_OK;
}

void TempScene::Update()
{
    mario.Update();
    mushroom.Update();
}

void TempScene::Render(HDC hdc)
{   
    mario.Render(hdc);
    mushroom.Render(hdc);
}

void TempScene::Release()
{
}
