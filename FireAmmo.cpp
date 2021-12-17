#include "FireAmmo.h"
#include "MacroCollection.h"
#include "GameDataContainer.h"
#include "Input.h"
#include "Image.h"

void FireAmmo::UpdateCollider()
{
    SetRect(&collider, pos.x - img->GetFrameWidth() / 2,
        pos.y - img->GetFrameHeight() / 2,
        pos.x + img->GetFrameWidth() / 2,
        pos.y + img->GetFrameHeight() / 2);
}

bool FireAmmo::OnCollisionEnter(RECT rc1, RECT rc2)
{
    if (rc1.left > rc2.right - GLOBAL_POS)	return false;
    if (rc1.right < rc2.left - GLOBAL_POS)  return false;
    if (rc1.top > rc2.bottom)	            return false;
    if (rc1.bottom < rc2.top)	            return false;

    return true;
}

void FireAmmo::ChangeAnimationFrame()
{
    elapsedTime += DELETA_TIME;
    if (elapsedTime > 0.1f)
    {
        ++frameX;
        if (img->GetMaxFrameX() - 3 <= frameX)  // 이미지의 마지막 3개의 프래임은 폭발 프레임
        {
            frameX = 0;
        }
        elapsedTime = 0.0f;
    }
}

void FireAmmo::ChangeBoundDirection()
{
    if (boundDirection == BoundDirection::Down)
    {
        boundDirection = BoundDirection::Up;
    }
    else
    {
        boundDirection = BoundDirection::Down;
    }
}

void FireAmmo::UpdatePosition()
{
    if (moveDirection == MoveDirection::Right)
    {
        pos.x += speed * DELETA_TIME;
    }
    else
    {
        pos.x -= speed * DELETA_TIME;
    }

    if (boundDirection == BoundDirection::Down)
    {
        pos.y += speed * DELETA_TIME;
    }
    else
    {
        pos.y -= speed * DELETA_TIME;
    }

}

void FireAmmo::Explosion()
{
    // 4 5 6 후 삭제
    elapsedTime += DELETA_TIME;

    if (frameX == 6)
    {
        if (elapsedTime > 0.05f)
        {
            /*isDead = true;
            isExploding = false;
            pos = { 0, 0 };*/
            Init();
        }
        return;
    }

    if (elapsedTime > 0.05f)
    {
        switch (frameX)
        {
        case 4:
        case 5:
            ++frameX;
            break;
        default:
            frameX = 4;
            break;
        }
        elapsedTime = 0.0f;
    }
}

HRESULT FireAmmo::Init()
{
    pos = { WIN_SIZE_X / 5, WIN_SIZE_Y / 2 };

    frameX = 0;

    nowTileIndexX = 0;
    nowTileIndexY = 0;

    boundDirection = BoundDirection::Down;
    moveDirection = MoveDirection::Right;

    isDead = false;
    isExploding = false;

    jumpHeight = 0.0f;
    elapsedTime = 0.0f;

    UpdateCollider();

    return S_OK;
}

void FireAmmo::Update()
{
    if (Input::GetButtonDown(VK_SPACE))
    {
        //ChangeBoundDirection();
        Init();
        boundDirection = BoundDirection::Down;
        isDead = false;
    }
    /*---------------------------------------------*/
    if (isDead == true)
    {
        return;
    }

    if (isExploding == true)
    {
        Explosion();
        return;
    }

    nowTileIndexX = (pos.x + GLOBAL_POS) / INGAME_RENDER_TILE_WIDHT_COUNT;
    nowTileIndexY = pos.y / MAP_HEIGHT;
    
    // 위에서 아래 방향으로 가다 충돌
    if (TILE_DATA[nowTileIndexY][nowTileIndexX].isCollider == true &&
        OnCollisionEnter(collider, TILE_DATA[nowTileIndexY][nowTileIndexX].rc) &&
        pos.y < TILE_DATA[nowTileIndexY][nowTileIndexX].rc.top)
    {
        ChangeBoundDirection();
    }
    // 앞, 뒤의 타일과 충돌했을 때
    else if ((TILE_DATA[nowTileIndexY][nowTileIndexX/* + 1*/].isCollider == true &&
        OnCollisionEnter(collider, TILE_DATA[nowTileIndexY][nowTileIndexX/* + 1*/].rc)) ||
        (TILE_DATA[nowTileIndexY][nowTileIndexX/* - 1*/].isCollider == true &&
            OnCollisionEnter(collider, TILE_DATA[nowTileIndexY][nowTileIndexX/* - 1*/].rc)))
    {
        isExploding = true;
        return;
    }

    UpdatePosition();

    // 화면 밖으로 안나가도록 처리
    if (pos.x < 0 || pos.x > WIN_SIZE_X)
    {
        isDead = true;
    }

    ChangeAnimationFrame();
    
    UpdateCollider();
}

void FireAmmo::Render(HDC hdc)
{
    // 콜라이더
    Rectangle(hdc, collider.left, collider.top, collider.right, collider.bottom);
    // 현재 위치
    Rectangle(hdc, TILE_DATA[nowTileIndexY][nowTileIndexX].rc.left - GLOBAL_POS,
        TILE_DATA[nowTileIndexY][nowTileIndexX].rc.top,
        TILE_DATA[nowTileIndexY][nowTileIndexX].rc.right - GLOBAL_POS,
        TILE_DATA[nowTileIndexY][nowTileIndexX].rc.bottom);

    img->Render(hdc, pos.x, pos.y, frameX, 0);

    //pos위치
    Rectangle(hdc, pos.x - 1, pos.y - 1, pos.x + 1, pos.y + 1);
}

void FireAmmo::Release()
{
}
