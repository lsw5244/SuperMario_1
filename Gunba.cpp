#include "Gunba.h"
#include "Image.h"
#include "Input.h"
#include "MacroCollection.h"
#include "GameDataContainer.h"

void Gunba::ChangeDirection()
{
    speed *= -1.0f;
    if (frameY == 0)
    {
        ++frameY;
    }
    else
    {
        frameY = 0;
    }
}

void Gunba::ChangeAnimationFrame()
{
    /*
        FrameX          FrameY
        0. 걷기 1        0. 오른쪽 바라보기(향하기)
        1. 걷기 2        1. 왼쪽 바라보기(향하기)
        2. 밟히기
        3. 죽기   
    */
    elapsedTime += DELETA_TIME;
    if (elapsedTime > 0.1f)
    {
        switch (frameX)
        {
        case 0:
            ++frameX;
            break;
        default:
            frameX = 0;
            break;
        }
        elapsedTime = 0.0f;
    }
    
}

void Gunba::UpdateCollider()
{
    SetRect(&collider, pos.x - (float)img->GetFrameWidth() / 2,
        pos.y - img->GetFrameWidth() / 2,
        pos.x + img->GetFrameWidth() / 2,
        pos.y + img->GetFrameHeight() / 2);
}

bool Gunba::OnCollisionEnter(RECT rect, RECT tileRect)
{
    if (rect.left > tileRect.right - GLOBAL_POS)	return false;
    if (rect.right < tileRect.left - GLOBAL_POS)	return false;
    if (rect.top > tileRect.bottom)             	return false;
    if (rect.bottom < tileRect.top)             	return false;

    return true;
}

void Gunba::CheckIsGround()
{
    if (TILE_DATA[nowTileIndexY][nowTileIndexX].isCollider == true &&
        collider.bottom > TILE_DATA[nowTileIndexY][nowTileIndexX].rc.top)
    {
        isGround = true;
    }
    else
    {
        isGround = false;
    }
}

HRESULT Gunba::Init()
{
    pos = { 0, 0 };
    UpdateCollider();

    isDead = false;

    frameY = MoveDirection::Right;

    return S_OK;
}

void Gunba::Update()
{
    if (Input::GetButtonDown('C') && isDead == false)
    {
        ChangeDirection();
    }
    /*---------------------*/
    if (isDead == true)
    {
        return;
    }

    //if(frameY == 0 && // 오른쪽 향할 때
    //    TILE_DATA[nowTileIndexY][nowTileIndexX].isCollider == true// &&
    //    
    //    )

    CheckIsGround();

    ChangeAnimationFrame();
 
    pos.x += speed * DELETA_TIME;
    if (isGround == false)
    {
        pos.y += gravity * DELETA_TIME;
    }
    UpdateCollider();

    nowTileIndexX = (pos.x + GLOBAL_POS) / INGAME_RENDER_TILE_WIDHT_COUNT;
    nowTileIndexY = pos.y / MAP_HEIGHT;
}

void Gunba::Render(HDC hdc)
{
    if (isDead == true)
        return;

    

    Rectangle(hdc, TILE_DATA[nowTileIndexY][nowTileIndexX].rc.left, TILE_DATA[nowTileIndexY][nowTileIndexX].rc.top, TILE_DATA[nowTileIndexY][nowTileIndexX].rc.right, TILE_DATA[nowTileIndexY][nowTileIndexX].rc.bottom);

    Rectangle(hdc, collider.left, collider.top, collider.right, collider.bottom);

    img->Render(hdc, pos.x, pos.y, frameX, frameY);

    Rectangle(hdc, pos.x - 3, pos.y - 3, pos.x + 3, pos.y + 3);

}

void Gunba::Release()
{
}
