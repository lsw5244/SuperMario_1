#include "Mushroom.h"
#include "Image.h"
#include "MacroCollection.h"
#include "GameDataContainer.h"

void Mushroom::AutoMove()
{
    if(moveDirection == MoveDirection::Right)
    {
        if (PLAYER->GetCurrSpeed() + PLAYER->GetPos().x > WIN_SIZE_X / 2)
        {
            pos.x += speed * DELETA_TIME - PLAYER->GetCurrSpeed();
        }
        else
        {
            pos.x += speed * DELETA_TIME;
        }
    }
    else
    {
        pos.x -= speed * DELETA_TIME;
    }

    if (CheckIsGround() == false)
    {
        pos.y += gravity * DELETA_TIME;
    }
}

void Mushroom::ChangeDirection()
{
    if (moveDirection == MoveDirection::Right &&
        TILE_DATA[nowTileIndexY][nowTileIndexX].isCollider == true &&
        collider.right > TILE_DATA[nowTileIndexY][nowTileIndexX].rc.left
        )
    {
        moveDirection = MoveDirection::Left;
    }
    
    if (moveDirection == MoveDirection::Left &&
        TILE_DATA[nowTileIndexY][nowTileIndexX].isCollider == true &&
        collider.left < TILE_DATA[nowTileIndexY][nowTileIndexX].rc.right
        )
    {
        moveDirection = MoveDirection::Right;
    }
}

bool Mushroom::CheckIsGround()
{
    if (TILE_DATA[nowTileIndexY][nowTileIndexX].isCollider == true &&
        collider.bottom > TILE_DATA[nowTileIndexY][nowTileIndexX].rc.top)
    {
        return true;
    }
    return false;
}

HRESULT Mushroom::Init()
{
    img = ImageManager::GetInstance()->FindImage("Image/Item/Mushroom.bmp");
    pos = { WIN_SIZE_X / 2, WIN_SIZE_Y / 2 };
    UpdateCollider();

    isDead = false;

    moveDirection = MoveDirection::Left;
    return S_OK;
}

void Mushroom::Update()
{
    if (isDead == true)
        return;

    ChangeDirection();

    AutoMove();

    UpdateCollider();

    nowTileIndexX = (pos.x + GLOBAL_POS) / INGAME_RENDER_TILE_WIDHT_COUNT;
    nowTileIndexY = pos.y / MAP_HEIGHT;

    Destroy();
}

void Mushroom::Render(HDC hdc)
{
    if (isDead == true)
        return;

    Rectangle(hdc, collider.left, collider.top, collider.right, collider.bottom);

    img->Render(hdc, pos.x, pos.y, 0, 0);
}

void Mushroom::Release()
{
}
