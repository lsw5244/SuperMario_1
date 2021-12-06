#include "Gunba.h"
#include "Image.h"
#include "Input.h"

void Gunba::AutoMove()
{
    moveSpeed *= -1.0f;
    if (frameY == 0)
    {
        ++frameY;
    }
    else
    {
        frameY = 0;
    }
}

void Gunba::AnimationFrameChanger()
{
    /*
        FrameX          FrameY
        0. 걷기 1        0. 오른쪽 바라보기(향하기)
        1. 걷기 2        1. 왼쪽 바라보기(향하기)
        2. 밟히기
        3. 죽기   
    */

    switch (frameX) // TODO : 프레임 변화는 딜레이 주기
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
    AnimationFrameChanger();
    if (Input::GetButtonDown('C') && isDead == false)
    {
        AutoMove();
    }
    cout << moveSpeed << endl;
    cout << frameY << endl;
    pos.x += moveSpeed;
}

void Gunba::Render(HDC hdc)
{
    img->Render(hdc, pos.x, pos.y, frameX, frameY);
}

void Gunba::Release()
{
}
