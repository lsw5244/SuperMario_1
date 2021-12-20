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
        0. �ȱ� 1        0. ������ �ٶ󺸱�(���ϱ�)
        1. �ȱ� 2        1. ���� �ٶ󺸱�(���ϱ�)
        2. ������
        3. �ױ�   
    */

    switch (frameX) // TODO : ������ ��ȭ�� ������ �ֱ�
    {
    case 0 :
        ++frameX;
        break;
    default:
        frameX = 0;
        break;
    }
}

HRESULT Gunba::Init()
{
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

    ChangeAnimationFrame();
 
    pos.x += speed;

    nowTileIndexX = (pos.x + GLOBAL_POS) / INGAME_RENDER_TILE_WIDHT_COUNT;
    nowTileIndexY = pos.y / MAP_HEIGHT;
}

void Gunba::Render(HDC hdc)
{
    img->Render(hdc, pos.x, pos.y, frameX, frameY);
}

void Gunba::Release()
{
}
