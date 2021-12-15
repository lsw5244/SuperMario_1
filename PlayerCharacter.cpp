#include "PlayerCharacter.h"
#include "Image.h"
#include "Input.h"
#include "MacroCollection.h"
#include "GameDataContainer.h"

#define mapWid 16   // 게임 화면에 보이는 총 타일 수는 16개

void PlayerCharacter::UpdateCollider()
{
    SetRect(&collider, pos.x - (float)img->GetFrameWidth() / 2,
        pos.y - (img->GetFrameWidth() * min(level - 1 , 1)),  // 레벨이 오르면 top의 위치가 변경됨
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

void PlayerCharacter::Jump()
{
    // 점프하다 머리 박았을 때 처리
    if (TILE_DATA[nowTileIndexY - 1][nowTileIndexX].isCollider == true &&
        collider.top < TILE_DATA[nowTileIndexY][nowTileIndexX].rc.bottom - 1
        )
    {
        jumpEnd = true;
        currJumpPower = 0.0f;
    }

    if (isGround == false)
    {
        currJumpPower -= gravity;
        gravity += gravityAcceleration;
        gravity = min(gravity, maxGravity);
        //return;
    }

    if (TILE_DATA[nowTileIndexY + 1][nowTileIndexX].isCollider == true &&
        collider.bottom > TILE_DATA[nowTileIndexY][nowTileIndexX].rc.bottom
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
        return;
    }
    if (Input::GetButton('Z') && jumpEnd == false)
    {
        isGround = false;
        currJumpPower += jumpPower;

        //점프 최대높이
        if (currJumpPower >= maxJumpPower)
        {
            jumpEnd = true;
        }
        currJumpPower = min(currJumpPower, maxJumpPower);
    }
}

void PlayerCharacter::Move()
{
    if (isGround)
    {
        if (Input::GetButton(VK_RIGHT))
        {
            currSpeed += speed;
            currSpeed = min(currSpeed, maxSpeed);
            // 미끌어 질 때( 방향과 반대 방향 키 누를 때 ) 속도 줄이는 시간 보정
            if (currSpeed < 0 && currSpeed > -0.5f)
            {
                currSpeed = 0.0f;
            }

        }
        else if (Input::GetButton(VK_LEFT))
        {
            currSpeed -= speed;
            currSpeed = max(currSpeed, -maxSpeed);
            if (currSpeed > 0 && currSpeed < 0.5f)
            {
                currSpeed = 0.0f;
            }
        }
        else
        {
            if (frameY == MoveDirection::Right)
            {
                currSpeed -= resistance;
                currSpeed = max(currSpeed, 0);
            }
            if (frameY == MoveDirection::Left)
            {
                currSpeed += resistance;
                currSpeed = min(currSpeed, 0);
            }
        }
    }
}

void PlayerCharacter::PositionUpdater()
{
    bool canMove = true;
    float nextXpos = pos.x + currSpeed;
    // 왼쪽 나가기 방지
    if (nextXpos < 0)
    {
        canMove = false;
    }
    // 절반 넘어가기 방지
    if (nextXpos > WIN_SIZE_X / 2)
    {
        canMove = false;
        GameDataContainer::GetInstance()->SetGlobalPos(GLOBAL_POS + currSpeed);
        if (Input::GetButton(VK_LEFT) && currSpeed < 1.0f)
        {
            currSpeed = 0.0f;
        }
    }

    // 옆 쪽 타일이 콜라이더 타일이고 그 타일과 일정 거리 이상 가까워지면 pos를 업데이트 하지 않음
    if (TILE_DATA[nowTileIndexY][nowTileIndexX + 1].isCollider == true &&
        collider.right > TILE_DATA[nowTileIndexY][nowTileIndexX + 1].rc.left - GLOBAL_POS - 1 &&
        currSpeed > 0)
    {
        currSpeed = 0;
        canMove = false;
    }
    else if (TILE_DATA[nowTileIndexY][nowTileIndexX - 1].isCollider == true &&
        collider.left > TILE_DATA[nowTileIndexY][nowTileIndexX - 1].rc.right - GLOBAL_POS + 1 &&
        currSpeed < 0)
    {
        currSpeed = 0;
        canMove = false;
    }

    if (canMove == true)
    {
        pos.x += currSpeed;
    }

    if (isGround == false)
    {
        pos.y -= currJumpPower;
    }
}

void PlayerCharacter::AnimationFrameChanger()
{
    // 방향 애니메이션
    if (currSpeed < 0)
    {
        frameY = MoveDirection::Left;
    }
    else if (currSpeed > 0)
    {
        frameY = MoveDirection::Right;
    }
    // 서 있는 애니메이션
    if (currSpeed == 0)
    {
        frameX = PlayerAnimation::Idle;
    }

    // 달리는 애니메이션
    if (abs(currSpeed) > 0)
    {
        elapsedTime += DELETA_TIME;
        if (elapsedTime > animationDelay)
        {
            switch (frameX)
            {
            case PlayerAnimation::Run1:
            case PlayerAnimation::Run2:
                ++frameX;
                break;
            case PlayerAnimation::Run3:
            default:
                frameX = PlayerAnimation::Run1;
                break;
            }
            elapsedTime = 0;
            animationDelay = 0.15f - 0.15f * currSpeed;
        }
    }
    else
    {
        elapsedTime = 0;
    }

    // 방향전환 애니메이션
    if (currSpeed > 0) // 오른쪽 가는 중인데
    {
        if (Input::GetButton(VK_LEFT))
        {
            frameX = PlayerAnimation::ChangeDirection;
            return;
        }
    }
    if (currSpeed < 0)
    {
        if (Input::GetButton(VK_RIGHT))
        {
            frameX = PlayerAnimation::ChangeDirection;
            return;
        }
    }

    // 앉아있기
    if (Input::GetButton(VK_DOWN))
    {
        if (level != 1)
        {
            frameX = PlayerAnimation::Sit;
        }
    }

    // 점프
    if (isGround == false)
    {
        frameX = PlayerAnimation::Jump;
    }

    // 죽기
    if (isDead == true)
    {
        frameX = PlayerAnimation::Die;
    }

    // 커지기


    // 공격하기
    if (Input::GetButtonDown('X'))
    {
        frameX = PlayerAnimation::Attack;
    }

    // 깃발 잡기
}

void PlayerCharacter::AnimationFrameChanger(int frameX, int frameY)
{
    this->frameX = frameX;
    this->frameY = frameY;
}

HRESULT PlayerCharacter::Init()
{
    img = ImageManager::GetInstance()->FindImage("Image/SamllRedMario.bmp");

    isGround = true;

    pos.x = WIN_SIZE_X / 2;
    pos.y = WIN_SIZE_Y / 2;

    UpdateCollider();

    return S_OK;
}

void PlayerCharacter::Update()
{
    //cout << level << endl;
    cout << elapsedTime << endl;
    if (Input::GetButtonDown('G'))
    {
        level++;
        isGrowing = true;
    }

    if (Input::GetButtonDown('H') && isSmalling == false)
    {
        --level;
        Hit();
        return;
    }

    if (pos.y < 15)
    {
        return;
    }

    if (isDead == true)
        return;



    if (isGrowing == true)
    {
        LevelUp();
        return;
    }

    if (isSmalling == true)
    {
        Smalling();
        return;
    }



    UpdateCollider();

    nowTileIndexX = (pos.x / mapWid + GLOBAL_POS / mapWid) + 0.5f;//MAP_WIDTH;
    nowTileIndexY = pos.y / MAP_HEIGHT;

    if (Input::GetButtonDown(VK_SPACE)) // TODO : 죽는 조건 변경, 죽을 때 바닥으로 떨어지도록 구현
    {
        isDead = true;
        AnimationFrameChanger();
        return;
    }

    Jump();

    Move();

    AnimationFrameChanger();

    PositionUpdater();
}

void PlayerCharacter::Render(HDC hdc)
{
    //현재 콜라이더
    Rectangle(hdc, collider.left, collider.top, collider.right, collider.bottom);

    // 현재 위치 타일
    Rectangle(hdc, TILE_DATA[nowTileIndexY][nowTileIndexX].rc.left - GLOBAL_POS,
        TILE_DATA[nowTileIndexY][nowTileIndexX].rc.top,
        TILE_DATA[nowTileIndexY][nowTileIndexX].rc.right - GLOBAL_POS,
        TILE_DATA[nowTileIndexY][nowTileIndexX].rc.bottom);

    img->Render(hdc, (int)pos.x, (int)pos.y, frameX, frameY);

    //pos위치
    Rectangle(hdc, pos.x - 1, pos.y - 1, pos.x + 1, pos.y + 1);
}

void PlayerCharacter::Release()
{
}

void PlayerCharacter::LevelUp()
{
    // 1 : small, 2 :  big, 3 : fire
    elapsedTime += DELETA_TIME;
    if (frameX == PlayerAnimation::Grow3)
    {
        if (elapsedTime > 0.1f)
        {
            isGrowing = false;
            elapsedTime = 0;

            if (level == 2)
            {
                img = ImageManager::GetInstance()->FindImage("Image/Character/BigRedMario.bmp");
            }
            else
            {
                img = ImageManager::GetInstance()->FindImage("Image/Character/BigFireMario.bmp");
            }
            
            return;
        }
        return;
    }
  
    if (elapsedTime > 0.2f)
    {
        switch (frameX)
        {
        case PlayerAnimation::Grow1:
        case PlayerAnimation::Grow2:
            ++frameX;
            break;
        case PlayerAnimation::Grow3:
            break;
        default:
            AnimationFrameChanger(PlayerAnimation::Grow1, frameY);
            break;
        }
        elapsedTime = 0.0f;
    }
}

void PlayerCharacter::Smalling()
{
    elapsedTime += DELETA_TIME;
    if (frameX == PlayerAnimation::Grow3)
    {
        if (elapsedTime > 0.1f)
        {
            isSmalling = false;
            elapsedTime = 0;
            img = ImageManager::GetInstance()->FindImage("Image/Character/SamllRedMario.bmp");
            return;
        }
        return;
    }

    if (elapsedTime > 0.2f)
    {
        switch (frameX)
        {
        case PlayerAnimation::Grow1:
        case PlayerAnimation::Grow2:
            ++frameX;
            break;
        case PlayerAnimation::Grow3:
            break;
        default:
            AnimationFrameChanger(PlayerAnimation::Grow1, frameY);
            break;
        }
        elapsedTime = 0.0f;
    }
}

void PlayerCharacter::Hit()
{
    // 1 : small, 2 :  big, 3 : fire

    if (level < 1)
    {
        isDead = true;
        AnimationFrameChanger();
        return;
    }

    if (level < 3)
    {
        level = 1;
        isSmalling = true;
    }
}
