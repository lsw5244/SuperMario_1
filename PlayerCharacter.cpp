#include "PlayerCharacter.h"
#include "Image.h"
#include "Input.h"
#include "MacroCollection.h"
#include "GameDataContainer.h"

#define mapWid 16   // 게임 화면에 보이는 총 타일 수는 16개

void PlayerCharacter::UpdateCollider()
{
    SetRect(&collider, pos.x - img->GetFrameWidth() / 2,
        pos.y - (img->GetFrameWidth() * 0),  // 크기에 따라 나누는 수 달라야 함
        pos.x + img->GetFrameWidth() / 2,
        pos.y + img->GetFrameHeight() / 2);
}

bool PlayerCharacter::OnCollisionEnter(RECT rc1, RECT rc2)
{
    if (rc1.left > rc2.right)	return false;
    if (rc1.right < rc2.left)	return false;
    if (rc1.top > rc2.bottom)	return false;
    if (rc1.bottom < rc2.top)	return false;

    return true;
}

void PlayerCharacter::AnimationFrameChanger()
{
    // 14 * 2
    /*
    FrameX                              FrameY
    0. 서 있기                           0. 오른쪽 바라보기
    1. 달리기 1                          1. 왼쪽 바라보기
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
        if (Input::GetButtonDown(VK_RIGHT))
        {
            frameX = 4;
        }
        break;
    case MoveDirection::Right:
        if (Input::GetButtonDown(VK_LEFT))
        {
            frameX = 4;
        }
        break;
    }

    // 앉아있기
    if (Input::GetButtonDown(VK_DOWN))
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
    if (Input::GetButtonDown('X'))
    {
        frameX = 11;
    }

    // 깃발 잡기
}

HRESULT PlayerCharacter::Init()
{
    img = ImageManager::GetInstance()->FindImage("Image/SamllRedMario.bmp");

    pos.x = WIN_SIZE_X / 2;
    pos.y = WIN_SIZE_Y / 2;

    UpdateCollider();

    return S_OK;
}

void PlayerCharacter::Update()
{
    if (isDead == true)
        return;

    nowTileIndexX = pos.x / mapWid;
    nowTileIndexY = pos.y / MAP_HEIGHT;

    if (Input::GetButtonDown(VK_SPACE)) // TODO : 죽는 조건 변경, 죽을 때 바닥으로 떨어지도록 구현
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

    //if (pos.y > WIN_SIZE_Y / 2) // TODO : 바닥에 닿은 조건 변경하기
    if (TILE_DATA[nowTileIndexY + 1][nowTileIndexX].isCollider == true/* &&
        collider.bottom > TILE_DATA[nowTileIndexY][nowTileIndexX].rc.bottom*/
        )
    {
        isGround = true;
        gravity = 0.01f;
        currJumpPower = 0;
        jumpEnd = false;
    }
    else
    {
        isGround = false;
    }

    if (Input::GetButtonUp('Z'))
    {
        jumpEnd = true;
    }
    if (Input::GetButton('Z') && jumpEnd == false)
    {
        isGround = false;
        currJumpPower += jumpPower;
        // 위 블럭에 머리 닿았을 때
        if (TILE_DATA[nowTileIndexY - 1][nowTileIndexX].isCollider == true &&
            pos.y > TILE_DATA[nowTileIndexY][nowTileIndexX].rc.top
            )
        {
            jumpEnd = true;
            currJumpPower = 0.0f;
        }

        //점프 최대높이
        if (currJumpPower >= maxJumpPower)
        {
            jumpEnd = true;
        }
        currJumpPower = min(currJumpPower, maxJumpPower);
    }

    if (isGround)
    {
        if (Input::GetButton(VK_RIGHT))
        {
            if (pos.x < WIN_SIZE_X / 2)
            {
                currSpeed += speed;
                currSpeed = min(currSpeed, maxSpeed);
            }
        }
        else if (Input::GetButton(VK_LEFT))
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
        gravity += gravityAcceleration;
        gravity = min(gravity, maxGravity);
    }

    AnimationFrameChanger();
    // 왼쪽 넘어가기 방지 + 절반 이상 가지 않도록
    if (pos.x + currSpeed > 0 && pos.x + currSpeed < WIN_SIZE_X / 2)
    {
        pos.x += currSpeed;
    }
    else
    {
        // 절반 이상 넘어가려 할 때 globalPos더해주기
        if (currSpeed > 0)
        {
            GameDataContainer::GetInstance()->SetGlobalPos(GLOBAL_POS + currSpeed);
        }
    }

    pos.y -= currJumpPower;

    UpdateCollider();
}

void PlayerCharacter::Render(HDC hdc)
{
    Rectangle(hdc, collider.left, collider.top, collider.right, collider.bottom);


    // 현재 위치 타일
    Rectangle(hdc, TILE_DATA[nowTileIndexY][nowTileIndexX].rc.left,
        TILE_DATA[nowTileIndexY][nowTileIndexX].rc.top,
        TILE_DATA[nowTileIndexY][nowTileIndexX].rc.right,
        TILE_DATA[nowTileIndexY][nowTileIndexX].rc.bottom);

    img->Render(hdc, (int)pos.x, (int)pos.y, frameX, frameY);
}

void PlayerCharacter::Release()
{
}
