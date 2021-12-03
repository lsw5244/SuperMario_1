#include "PlayerCharacter.h"
#include "Image.h"

void PlayerCharacter::AnimationFrameChanger()
{
    // 14 * 2
    /*
    FrameX                              FrameY
    0. 서 있기                           0. 오른쪽 바라보기
    1. 달리기 1                         1. 왼쪽 바라보기
    2. 달리기 2
    3. 달리기 3
    4. 달리다 방향 전환하기
    5. 앉아있기
    6. 점프
    7. 죽기
    8. 커지기 1
    9. 커지기 2
    10. 커지기 3
    11. 공격하기
    12. 깃발 잡기 1
    13. 깃발 잡기 2*/
    // 좌 우 반전
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

    // 달리고 있는지 확인하기(달리기 만들기)
    if (abs(currSpeed) > 0) // frame x가 2 ~ 4 반복해야 함  TODO : 애니메이션 간의 딜레이 주기(애니메이션이 너무 빨리 바뀜)
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
    // 달리다 방향전환
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

    // 앉아있기
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
    {
        if (level != 1)
        {
            frameX = 5;
        }
    }

    // 점프
    if (isGround == false)
    {
        frameX = 6;
    }
    // 죽기
    if (isDead == true)
    {
        frameX = 7;
    }

    // 커지기

    // 공격하기
    if (KeyManager::GetSingleton()->IsOnceKeyDown('X'))
    {
        frameX = 11;
    }

    // 깃발 잡기
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

    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE)) // TODO : 죽는 조건 변경, 죽을 때 바닥으로 떨어지도록 구현
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

    if (pos.y > WIN_SIZE_Y / 2) // TODO : 바닥에 닿은 조건 변경하기
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
        else  // 속도 점점 줄여야 함
        {
            switch (direction)
            {
            case MoveDirection::Left:   // 스피드 높여야 함
                currSpeed += resistance; // 저항 ?
                currSpeed = min(currSpeed, 0);
                break;
            case MoveDirection::Right: // 스피드 줄여야 함
                currSpeed -= resistance; // 저항 ? resistance
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
