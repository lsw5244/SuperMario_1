#include "FireFlower.h"
#include "Image.h"
#include "MacroCollection.h"
#include "GameDataContainer.h"

void FireFlower::ChangeFrame()
{
    elapsedTime += DELETA_TIME;

    if (elapsedTime < animationDelay)
    {
        return;
    }
    if (frameX >= lastFrameX)
    {
        frameX = 0;
    }
    else
    {
        ++frameX;
    }
    elapsedTime = 0.0f;
}

HRESULT FireFlower::Init()
{
    img = ImageManager::GetInstance()->FindImage("Image/Item/FireFlower.bmp");

    pos = { WIN_SIZE_X / 2, WIN_SIZE_Y / 2 };

    UpdateCollider();

    return S_OK;
}

void FireFlower::Update()
{
    if (isDead == true)
        return;

    nowTileIndexX = (pos.x + GLOBAL_POS) / INGAME_RENDER_TILE_WIDHT_COUNT;
    nowTileIndexY = pos.y / MAP_HEIGHT;

    ChangeFrame();
}

void FireFlower::Render(HDC hdc)
{
    if (isDead == true)
        return;

    img->Render(hdc, pos.x, pos.y, frameX, 0);
}

void FireFlower::Release()
{
}
