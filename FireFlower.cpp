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

//void FireFlower::SpawnAnimation()
//{
//    pos.y -= spawnSpeed * DELETA_TIME;
//
//    spawnMoveDistance += spawnSpeed * DELETA_TIME;
//    cout << spawnMoveDistance << endl;
//    if (spawnMoveDistance > TILE_SIZE)
//    {
//        isDead = false;
//        isSpawning = false;
//        spawnMoveDistance = 0.0f;
//    }
//}

HRESULT FireFlower::Init()
{
    img = ImageManager::GetInstance()->FindImage("Image/Item/FireFlower.bmp");

    pos = { WIN_SIZE_X / 2, WIN_SIZE_Y / 2 };

    isDead = true;

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
    }

    if (isDead == true)
        return;

    nowTileIndexX = (pos.x + GLOBAL_POS) / INGAME_RENDER_TILE_WIDHT_COUNT;
    nowTileIndexY = pos.y / MAP_HEIGHT;

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

//void FireFlower::Spawn(POINTFLOAT pos)
//{
//    this->pos = pos;
//    isSpawning = true;
//}
