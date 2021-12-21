#include "Mushroom.h"
#include "Image.h"
#include "MacroCollection.h"
#include "GameDataContainer.h"
#include "Input.h"
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
    if (moveDirection == MoveDirection::Left &&
        TILE_DATA[nowTileIndexY - 1][nowTileIndexX - 1].isCollider == true &&
        OnCollisionEnter(collider, TILE_DATA[nowTileIndexY - 1][nowTileIndexX - 1].rc) == true)
    {
        moveDirection = MoveDirection::Right;
        return;
    }

    if (moveDirection == MoveDirection::Right &&
        TILE_DATA[nowTileIndexY - 1][nowTileIndexX + 1].isCollider == true &&
        OnCollisionEnter(collider, TILE_DATA[nowTileIndexY - 1][nowTileIndexX + 1].rc) == true)
    {
        moveDirection = MoveDirection::Left;
        rethrow_exception;
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

bool Mushroom::OnCollisionEnter(RECT rect, RECT tileRect)
{
    if (rect.left > tileRect.right - GLOBAL_POS)	return false;
    if (rect.right < tileRect.left - GLOBAL_POS)	return false;
    if (rect.top > tileRect.bottom)             	return false;
    if (rect.bottom < tileRect.top)             	return false;

    return true;
}

HRESULT Mushroom::Init()
{
    img = ImageManager::GetInstance()->FindImage("Image/Item/Mushroom.bmp");
    pos = { WIN_SIZE_X / 2, WIN_SIZE_Y / 2 };
    UpdateCollider();

    isDead = true;
    isSpawning = false;

    moveDirection = MoveDirection::Right;
    return S_OK;
}

void Mushroom::Update()
{
    if (Input::GetButtonDown(VK_SPACE))
    {
        Spawn({ WIN_SIZE_X / 2, WIN_SIZE_Y / 2 });
    }
    if (isSpawning == true)
    {
        SpawnAnimation();
        return;
    }

    if (isDead == true)
        return;

    ChangeDirection();

    AutoMove();

    UpdateCollider();

    if (CollideWithPlayer() == true)
    {
        if (PLAYER->GetLevel() < 3)
        {
            PLAYER->LevelUp();
        }
        Destroy();
    }

    nowTileIndexX = (pos.x + GLOBAL_POS) / INGAME_RENDER_TILE_WIDHT_COUNT;
    nowTileIndexY = pos.y / MAP_HEIGHT;

    // 화면 나가기 방지
    if (pos.x > WIN_SIZE_X || pos.x < 0)
    {
        Destroy();
    }
    
}

void Mushroom::Render(HDC hdc)
{
    if (isDead == true && isSpawning == false)
        return;

    Rectangle(hdc, collider.left, collider.top, collider.right, collider.bottom);

    img->Render(hdc, pos.x, pos.y, 0, 0);
}

void Mushroom::Release()
{
}
