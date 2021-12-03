#include "PlayerCharacter.h"
#include "Image.h"

void PlayerCharacter::AnimationFrameChanger()
{
    // 14 * 2
    /*
    FrameX                              FrameY
    0. �� �ֱ�                           0. ������ �ٶ󺸱�
    1. �޸��� 1                         1. ���� �ٶ󺸱�
    2. �޸��� 2
    3. �޸��� 3
    4. �޸��� ���� ��ȯ�ϱ�
    5. �ɾ��ֱ�
    6. ����
    7. �ױ�
    8. Ŀ���� 1
    9. Ŀ���� 2
    10. Ŀ���� 3
    11. �����ϱ�
    12. ��� ��� 1
    13. ��� ��� 2*/
    // �� �� ����
    switch (direction)
    {
    case MoveDirection::Left:
        frameY = 1;
        break;
    case MoveDirection::Right:
        frameY = 0;
        break;
    }
    if (currSpeed == 0)
    {
        frameX = 0;
    }

    // �޸��� �ִ��� Ȯ���ϱ�(�޸��� �����)
    if (abs(currSpeed) > 0) // frame x�� 2 ~ 4 �ݺ��ؾ� ��  TODO : �ִϸ��̼� ���� ������ �ֱ�(�ִϸ��̼��� �ʹ� ���� �ٲ�)
    {
        switch (frameX)
        {
        case 1:
        case 2:
            ++frameX;
            break;
        case 3:
        default:
            frameX = 1;
            break;
        }
    }
    // �޸��� ������ȯ
    switch (direction)
    {
    case MoveDirection::Left:
        if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
        {
            frameX = 4;
        }
        break;
    case MoveDirection::Right:
        if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
        {
            frameX = 4;
        }
        break;
    }

    // �ɾ��ֱ�
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
    {
        if (level != 1)
        {
            frameX = 5;
        }
    }

    // ����
    if (isGround == false)
    {
        frameX = 6;
    }
    // �ױ�
    if (isDead == true)
    {
        frameX = 7;
    }

    // Ŀ����

    // �����ϱ�
    if (KeyManager::GetSingleton()->IsOnceKeyDown('X'))
    {
        frameX = 11;
    }

    // ��� ���
}

HRESULT PlayerCharacter::Init()
{
    img = ImageManager::GetSingleton()->FindImage("Image/SamllRedMario.bmp");

    pos.x = WIN_SIZE_X / 2;
    pos.y = WIN_SIZE_Y / 2;

    return S_OK;
	return S_OK;
}

void PlayerCharacter::Update()
{
    if (isDead == true)
        return;

    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE)) // TODO : �״� ���� ����, ���� �� �ٴ����� ���������� ����
    {
        isDead = true;
        AnimationFrameChanger();
        return;
    }

    //direction = (currSpeed < 0) ? Direction::Left : Direction::Right;
    if (currSpeed < 0)
    {
        direction = MoveDirection::Left;
    }
    else if (currSpeed > 0)
    {
        direction = MoveDirection::Right;
    }

    if (pos.y > WIN_SIZE_Y / 2) // TODO : �ٴڿ� ���� ���� �����ϱ�
    {
        isGround = true;
        gravity = 0.1f;
        currJumpPower = 0;
        jumpEnd = false;
    }

    if (KeyManager::GetSingleton()->IsOnceKeyUp('Z'))
    {
        jumpEnd = true;
    }
    if (KeyManager::GetSingleton()->IsStayKeyDown('Z') && jumpEnd == false)
    {
        isGround = false;
        currJumpPower += jumpPower;
        if (currJumpPower >= maxJumpPower)
        {
            jumpEnd = true;
        }
        currJumpPower = min(currJumpPower, maxJumpPower);
    }

    if (isGround)
    {
        if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
        {
            currSpeed += speed;
            currSpeed = min(currSpeed, maxSpeed);
        }
        else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
        {
            currSpeed -= speed;
            currSpeed = max(currSpeed, -maxSpeed);
        }
        else  // �ӵ� ���� �ٿ��� ��
        {
            switch (direction)
            {
            case MoveDirection::Left:   // ���ǵ� ������ ��
                currSpeed += resistance; // ���� ?
                currSpeed = min(currSpeed, 0);
                break;
            case MoveDirection::Right: // ���ǵ� �ٿ��� ��
                currSpeed -= resistance; // ���� ? resistance
                currSpeed = max(currSpeed, 0);
                break;
            }
        }
    }

    if (isGround == false)
    {
        currJumpPower -= gravity;
        gravity += 0.002f;
    }

    AnimationFrameChanger();

    pos.x += currSpeed;
    pos.y -= currJumpPower;
}

void PlayerCharacter::Render(HDC hdc)
{
    img->Render(hdc, pos.x, pos.y, frameX, frameY);
}

void PlayerCharacter::Release()
{
}
