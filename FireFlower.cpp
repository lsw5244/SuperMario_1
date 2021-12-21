#include "FireFlower.h"
#include "Image.h"
#include "MacroCollection.h"
#include "GameDataContainer.h"
#include "Input.h"

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

    isDead = true;
    isSpawning = false;

    UpdateCollider();

    return S_OK;
}

void FireFlower::Update()
{
    if (Input::GetButtonDown(VK_SPACE))
    {
        Spawn({WIN_SIZE_X / 2, WIN_SIZE_Y / 2});
    }
    if (isSpawning == true)
    {
        SpawnAnimation();
        ChangeFrame();
    }

    if (isDead == true)
        return;

    //nowTileIndexX = (pos.x + GLOBAL_POS) / INGAME_RENDER_TILE_WIDHT_COUNT;
    //nowTileIndexY = pos.y / MAP_HEIGHT;

    if (CollideWithPlayer() == true)
    {
        if (PLAYER->GetLevel() < 3)
        {
            PLAYER->LevelUp();
        }
        Destroy();
    }

    AutoMove();

    UpdateCollider();

    // 화면 나가기 방지
    if (pos.x > WIN_SIZE_X || pos.x < 0)
    {
        Destroy();
    }

    ChangeFrame();
}

void FireFlower::Render(HDC hdc)
{
    if (isDead == true && isSpawning == false)
        return;

    img->Render(hdc, pos.x, pos.y, frameX, 0);
}

void FireFlower::Release()
{
}

void FireFlower::AutoMove()
{
    if (PLAYER->GetPos().x + PLAYER->GetCurrSpeed() > WIN_SIZE_X / 2)
    {
        pos.x -= PLAYER->GetCurrSpeed();
    }
}
