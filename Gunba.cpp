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
