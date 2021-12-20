#include "SpinCoin.h"
#include "MacroCollection.h"
#include "GameDataContainer.h"
#include "Image.h"

void SpinCoin::ChangeFrame()
{
    elapsedTime += DELETA_TIME;

    if (elapsedTime < animationDelay)
    {
        return;
    }
    if (frameX >= img->GetMaxFrameX() - 1)
    {
        frameX = 0;
    }
    else
    {
        ++frameX;
    }
    elapsedTime = 0.0f;
}

HRESULT SpinCoin::Init()
{
    img = ImageManager::GetInstance()->FindImage("Image/Item/SpinCoin.bmp");
    pos = { WIN_SIZE_X / 2, WIN_SIZE_Y / 2 };

    isDead = false;

    return S_OK;
}

void SpinCoin::Update()
{
    if (isDead == true)
        return;

    ChangeFrame();
}

void SpinCoin::Render(HDC hdc)
{
    if (isDead == true)
        return;

    img->Render(hdc, pos.x, pos.y, frameX, 0);
}

void SpinCoin::Release()
{
}
