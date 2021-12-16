#include "PlayerCharacter.h"
#include "Image.h"
#include "Input.h"
#include "MacroCollection.h"
#include "GameDataContainer.h"

void PlayerCharacter::UpdateCollider()
{
    SetRect(&collider, pos.x - (float)img->GetFrameWidth() / 2,
        pos.y - (img->GetFrameWidth() * min(level - 1 , 1)),  // ������ ������ top�� ��ġ�� �����
        pos.x + img->GetFrameWidth() / 2,
        pos.y + img->GetFrameHeight() / 2);
}

bool PlayerCharacter::OnCollisionEnter(RECT rc1, RECT rc2)
{
    if (rc1.left > rc2.right - GLOBAL_POS)	return false;
    if (rc1.right < rc2.left - GLOBAL_POS)	return false;
    if (rc1.top > rc2.bottom)	return false;
    if (rc1.bottom < rc2.top)	return false;

    return true;
}

void PlayerCharacter::Jump()
{
    // �����ϴ� �Ӹ� �ھ��� �� ó��
    if (TILE_DATA[nowTileIndexY - 1][nowTileIndexX].isCollider == true &&
        collider.top < TILE_DATA[nowTileIndexY][nowTileIndexX].rc.bottom - 1
        )
    {
        jumpEnd = true;
        currJumpPower = 0.0f;
    }

    if (isGround == false)
    {
        currJumpPower -= gravity * DELETA_TIME;
        gravity += gravityAcceleration * DELETA_TIME;
        gravity = min(gravity, maxGravity);
        //return;
    }

    if (TILE_DATA[nowTileIndexY + 1][nowTileIndexX].isCollider == true &&
        collider.bottom > TILE_DATA[nowTileIndexY][nowTileIndexX].rc.bottom
        )
    {
        isGround = true;
        gravity = 300.0f;
        currJumpPower = 0.0f;
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
        currJumpPower += (jumpPower/* + jumpPower*/) * DELETA_TIME;
        //���� �ִ����
        if (currJumpPower >= maxJumpPower)
        {
            jumpEnd = true;
            currJumpPower = maxJumpPower;
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
            currSpeed += acceleration * DELETA_TIME;
            currSpeed = min(currSpeed, maxSpeed * DELETA_TIME);
            // �̲��� �� ��( ����� �ݴ� ���� Ű ���� �� ) �ӵ� ���̴� �ð� ����
            if (currSpeed < 0 && currSpeed > -0.5f)
            {
                currSpeed = 0.0f;
            }

        }
        else if (Input::GetButton(VK_LEFT))
        {
            currSpeed -= acceleration * DELETA_TIME;
            currSpeed = max(currSpeed, -maxSpeed * DELETA_TIME);
            if (currSpeed > 0 && currSpeed < 0.5f)
            {
                currSpeed = 0.0f;
            }
        }
        else
        {
            if (frameY == MoveDirection::Right)
            {
                currSpeed -= resistance * DELETA_TIME;
                currSpeed = max(currSpeed, 0);
            }
            if (frameY == MoveDirection::Left)
            {
                currSpeed += resistance * DELETA_TIME;
                currSpeed = min(currSpeed, 0);
            }
        }
    }
}

void PlayerCharacter::PositionUpdater()
{
    bool canMove = true;
    float nextXpos = pos.x + currSpeed;
    // ���� ������ ����
    if (nextXpos < 0)
    {
        canMove = false;
    }
    // ���� �Ѿ�� ����
    if (nextXpos > WIN_SIZE_X / 2)
    {
        canMove = false;
        GameDataContainer::GetInstance()->SetGlobalPos(GLOBAL_POS + currSpeed);
        if (Input::GetButton(VK_LEFT) && currSpeed < 1.0f)
        {
            currSpeed = 0.0f;
        }
    }

    // �� �� Ÿ���� �ݶ��̴� Ÿ���̰� �� Ÿ�ϰ� ���� �Ÿ� �̻� ��������� pos�� ������Ʈ ���� ����
    if (TILE_DATA[nowTileIndexY][nowTileIndexX + 1].isCollider == true &&
        OnCollisionEnter(collider, TILE_DATA[nowTileIndexY][nowTileIndexX + 1].rc) == true &&
        currSpeed > 0)
    {
        currSpeed = 0;
        canMove = false;
    }
    else if (TILE_DATA[nowTileIndexY][nowTileIndexX - 1].isCollider == true &&
        OnCollisionEnter(collider, TILE_DATA[nowTileIndexY][nowTileIndexX - 1].rc) == true &&
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
        pos.y -= currJumpPower * DELETA_TIME;
    }
}

void PlayerCharacter::ChagneAnimationFrame()
{
    // ���� �ִϸ��̼�
    if (currSpeed < 0)
    {
        frameY = MoveDirection::Left;
    }
    else if (currSpeed > 0)
    {
        frameY = MoveDirection::Right;
    }
    // �� �ִ� �ִϸ��̼�
    if (currSpeed == 0)
    {
        frameX = PlayerAnimation::Idle;
    }

    // �޸��� �ִϸ��̼�
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
            animationDelay = max(0.15f - 0.15f * abs(currSpeed), 0.05f); // 0.05�� �ּ� ������
        }
    }
    else
    {
        elapsedTime = 0;
    }

    // ����
    if (isGround == false)
    {
        frameX = PlayerAnimation::Jump;
        return;
    }

    // ������ȯ �ִϸ��̼�
    if (currSpeed > 0) // ������ ���� ���ε�
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

    // �ɾ��ֱ�
    if (Input::GetButton(VK_DOWN))
    {
        if (level != 1)
        {
            frameX = PlayerAnimation::Sit;
        }
    }

    // �ױ�
    if (isDead == true)
    {
        frameX = PlayerAnimation::Die;
    }

    // Ŀ����


    // �����ϱ�
    if (Input::GetButtonDown('X'))
    {
        frameX = PlayerAnimation::Attack;
    }

    // ��� ���
}

void PlayerCharacter::ChagneAnimationFrame(int frameX, int frameY)
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
    //cout << elapsedTime << endl;
    if (Input::GetButtonDown('G'))
    {
        elapsedTime = 0.0f;
        level++;
        isGrowing = true;
    }

    if (Input::GetButtonDown('H') && isSmalling == false)
    {
        elapsedTime = 0.0f;
        --level;
        Hit();
        return;
    }

    if (pos.y < 15)
    {
        return;
    }

    if (isDead == true)
    {
        return;
    }

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

    Jump();

    Move();

    ChagneAnimationFrame();

    PositionUpdater();

    nowTileIndexX = (pos.x + GLOBAL_POS) / INGAME_RENDER_TILE_WIDHT_COUNT;
    nowTileIndexY = pos.y / MAP_HEIGHT;

    UpdateCollider();
}

void PlayerCharacter::Render(HDC hdc)
{
    //���� �ݶ��̴�
    Rectangle(hdc, collider.left, collider.top, collider.right, collider.bottom);

    // ���� ��ġ Ÿ��
    Rectangle(hdc, TILE_DATA[nowTileIndexY][nowTileIndexX].rc.left - GLOBAL_POS,
        TILE_DATA[nowTileIndexY][nowTileIndexX].rc.top,
        TILE_DATA[nowTileIndexY][nowTileIndexX].rc.right - GLOBAL_POS,
        TILE_DATA[nowTileIndexY][nowTileIndexX].rc.bottom);

    img->Render(hdc, (int)pos.x, (int)pos.y, frameX, frameY);

    //pos��ġ
    Rectangle(hdc, pos.x - 1, pos.y - 1, pos.x + 1, pos.y + 1);
}

void PlayerCharacter::Release()
{
}

void PlayerCharacter::LevelUp()
{
    // 1 : small, 2 :  big, 3 : fire
    elapsedTime += DELETA_TIME;

    if (level == 2)
    {
        if (frameX == PlayerAnimation::Grow3)
        {
            if (elapsedTime > 0.1f)
            {
                isGrowing = false;
                elapsedTime = 0;

                img = ImageManager::GetInstance()->FindImage("Image/Character/BigRedMario.bmp");

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
                ChagneAnimationFrame(PlayerAnimation::Grow1, frameY);
                break;
            }
            elapsedTime = 0.0f;
        }
    }
    else
    {        
        if (nowImageIdChecker > 5)
        {
            img = ImageManager::GetInstance()->FindImage("Image/Character/BigFireMario.bmp");
            elapsedTime = 0.0f;
            nowImageIdChecker = 0;
            isGrowing = false;
            return;
        }
        
        if (elapsedTime > 0.2f)
        {
            switch (nowImageIdChecker % 2)
            {
            case 1:
                img = ImageManager::GetInstance()->FindImage("Image/Character/BigFireMario.bmp");
                break;
            default:
                img = img = ImageManager::GetInstance()->FindImage("Image/Character/BigRedMario.bmp");
                break;
            }
            elapsedTime = 0.0f;
            ++nowImageIdChecker;
        }
        
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
            ChagneAnimationFrame(PlayerAnimation::Grow1, frameY);
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
        ChagneAnimationFrame();
        return;
    }

    if (level < 3)
    {
        level = 1;
        isSmalling = true;
    }
}
