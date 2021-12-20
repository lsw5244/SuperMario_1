#include "Gunba.h"
#include "Image.h"
#include "Input.h"
#include "MacroCollection.h"
#include "GameDataContainer.h"

void Gunba::ChangeDirection()
{
   // 왼쪽 가다 충돌
   if (frameY == 1 &&
       TILE_DATA[nowTileIndexY - 1][nowTileIndexX - 1].isCollider == true &&
       OnCollisionEnter(collider, TILE_DATA[nowTileIndexY - 1][nowTileIndexX - 1].rc) == true)
       /*collider.left < TILE_DATA[nowTileIndexY - 1][nowTileIndexX - 1].rc.right)*/
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
       return;
   }
   // 오른쪽 가다가 충돌
   if (frameY == 0 &&
       TILE_DATA[nowTileIndexY - 1][nowTileIndexX + 1].isCollider == true &&
       OnCollisionEnter(collider, TILE_DATA[nowTileIndexY - 1][nowTileIndexX + 1].rc) == true)      
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
       return;
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
    SetRect(&collider, pos.x - img->GetFrameWidth() / 2,
        pos.y - img->GetFrameWidth() / 2,
        pos.x + img->GetFrameWidth() / 2,
        pos.y + img->GetFrameHeight() / 2);
}

void Gunba::UpdatePosition()
{
    if (PLAYER->GetCurrSpeed() + PLAYER->GetPos().x > WIN_SIZE_X / 2)
    {
        pos.x += speed * DELETA_TIME - (int)PLAYER->GetCurrSpeed();
    }
    else
    {
        pos.x += speed * DELETA_TIME;
    }

    if (isGround == false)
    {
        pos.y += gravity * DELETA_TIME;
    }
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

void Gunba::CheckOutWindow()
{
    if (pos.x < 0 || pos.x > WIN_SIZE_X || pos.y < 0 || pos.y > WIN_SIZE_Y)
    {
        isDead = true;
    }
}

bool Gunba::CheckFireHit()
{
    AMMO_MANAGER;

    return false;
}

bool Gunba::CollideWithPlayer()
{
    if (PLAYER->GetRect().left > collider.right)	return false;
    if (PLAYER->GetRect().right < collider.left)	return false;
    if (PLAYER->GetRect().top > collider.bottom)	return false;
    if (PLAYER->GetRect().bottom < collider.top)	return false;

    return true;
}

void Gunba::Trampled()
{
    elapsedTime += DELETA_TIME;
    if (elapsedTime > 1.0f)
    {
        isDead = true;
    }
    frameX = 2; // 밟히기  
}

HRESULT Gunba::Init()
{
    pos = { 0, 0 };
    UpdateCollider();

    isDead = false;
    isDying = false;

    frameY = 1;     // 왼쪽 향함

    return S_OK;
}

void Gunba::Update()
{
    if (Input::GetButtonDown('C') && isDead == false)
    {
        Die();
    }
    /*---------------------*/

    if (isDying == true)
    {
        Trampled();
        return;
    }

    if (isDead == true)
    {
        return;
    }

    // 플레이어와 충돌
    if (CollideWithPlayer() == true)
    {
        // 위에서 밟힌거면 죽기
        if (PLAYER->GetRect().bottom < pos.y)
        {
            Die();
            return;
        }
        else
        {
            PLAYER->GetDamage();
        }
    }
    if (CheckFireHit() == true)
    {
        Die();
        return;
    }

    CheckIsGround();

    ChangeAnimationFrame();

    UpdatePosition();

    UpdateCollider();

    ChangeDirection();

    nowTileIndexX = (pos.x + GLOBAL_POS) / INGAME_RENDER_TILE_WIDHT_COUNT;
    nowTileIndexY = pos.y / MAP_HEIGHT;

    CheckOutWindow();
}

void Gunba::Render(HDC hdc)
{
    if (isDead == true)
        return;

    Rectangle(hdc, TILE_DATA[nowTileIndexY - 1][nowTileIndexX].rc.left - GLOBAL_POS,
        TILE_DATA[nowTileIndexY - 1][nowTileIndexX].rc.top,
        TILE_DATA[nowTileIndexY - 1][nowTileIndexX].rc.right - GLOBAL_POS,
        TILE_DATA[nowTileIndexY - 1][nowTileIndexX].rc.bottom);

    img->Render(hdc, pos.x, pos.y, frameX, frameY);

    //Rectangle(hdc, pos.x - 3, pos.y - 3, pos.x + 3, pos.y + 3);

}

void Gunba::Release()
{
}

void Gunba::Die()
{
    elapsedTime = 0.0f;
    isDying = true;
}
