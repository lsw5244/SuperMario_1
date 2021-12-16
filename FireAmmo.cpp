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
    if (rc1.right < rc2.left)	            return false;
    if (rc1.top > rc2.bottom - GLOBAL_POS)	return false;
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

HRESULT FireAmmo::Init()
{
    pos = { WIN_SIZE_X / 3, WIN_SIZE_Y / 2 };

    UpdateCollider();

    return S_OK;
}

void FireAmmo::Update()
{
    if (Input::GetButtonDown(VK_SPACE))
    {
        ChangeBoundDirection();
    }
    /*---------------------------------------------*/

    nowTileIndexX = (pos.x + GLOBAL_POS) / INGAME_RENDER_TILE_WIDHT_COUNT;
    nowTileIndexY = pos.y / MAP_HEIGHT;

    if (TILE_DATA[nowTileIndexY/* + 1*/][nowTileIndexX].isCollider == true &&
        OnCollisionEnter(collider, TILE_DATA[nowTileIndexY/* + 1*/][nowTileIndexX].rc))
    {
        ChangeBoundDirection();
    }

    pos.x += speed * DELETA_TIME;
    if (boundDirection == BoundDirection::Down)
    {
        pos.y += speed * DELETA_TIME;
    }
    else
    {
        pos.y -= speed * DELETA_TIME;
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
