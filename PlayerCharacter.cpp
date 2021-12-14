#include "PlayerCharacter.h"
#include "Image.h"
#include "Input.h"
#include "MacroCollection.h"
#include "GameDataContainer.h"

#define mapWid 16   // ���� ȭ�鿡 ���̴� �� Ÿ�� ���� 16��

void PlayerCharacter::UpdateCollider()
{
    SetRect(&collider, pos.x - (float)img->GetFrameWidth() / 2,
        pos.y - (img->GetFrameWidth() * 0),  // ũ�⿡ ���� ������ �� �޶�� ��
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

        //���� �ִ����
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
        }
        else if (Input::GetButton(VK_LEFT))
        {
            currSpeed -= speed;
            currSpeed = max(currSpeed, -maxSpeed);
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

        //if (Input::GetButton(VK_RIGHT))
        //{
        //    //if (pos.x < WIN_SIZE_X / 2)
        //    {
        //        currSpeed += speed;
        //        currSpeed = min(currSpeed, maxSpeed);
        //    }
        //}
        //else if (Input::GetButton(VK_LEFT))
        //{
        //    currSpeed -= speed;
        //    currSpeed = max(currSpeed, -maxSpeed);
        //}
        //else  // �ӵ� ���� �ٿ��� �� (�ƹ��͵� �ȴ��� )
        //{
        //    switch (frameY)
        //    {
        //    case MoveDirection::Left:   // ���ǵ� ������ ��
        //        currSpeed += resistance; // ���� ?
        //        currSpeed = min(currSpeed, 0);
        //        break;
        //    case MoveDirection::Right: // ���ǵ� �ٿ��� ��
        //        currSpeed -= resistance; // ���� ? resistance
        //        currSpeed = max(currSpeed, 0);
        //        break;
        //    default:
        //        break;
        //    }
        //}
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
        if (currSpeed < 1.0f)
        {
            currSpeed = 0.0f;
        }
    }

    // �� �� Ÿ���� �ݶ��̴� Ÿ���̰� �� Ÿ�ϰ� ���� �Ÿ� �̻� ��������� pos�� ������Ʈ ���� ����
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
    if (abs(currSpeed) > 0) // frame x�� 2 ~ 4 �ݺ��ؾ� ��  TODO : �ִϸ��̼� ���� ������ �ֱ�(�ִϸ��̼��� �ʹ� ���� �ٲ�)
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

    /*switch (frameY)
    {
    case MoveDirection::Left:
        if (Input::GetButtonDown(VK_RIGHT))
        {
            frameX = PlayerAnimation::ChangeDirection;
        }
        break;
    case MoveDirection::Right:
        if (Input::GetButtonDown(VK_LEFT))
        {
            frameX = PlayerAnimation::ChangeDirection;
        }
        break;
    }*/

    // �ɾ��ֱ�
    if (Input::GetButtonDown(VK_DOWN))
    {
        if (level != 1)
        {
            frameX = PlayerAnimation::Sit;
        }
    }

    // ����
    if (isGround == false)
    {
        frameX = PlayerAnimation::Jump;
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
    if (pos.y < 15)
    {
        return;
    }

    if (isDead == true)
        return;

    UpdateCollider();

    nowTileIndexX = (pos.x / mapWid + GLOBAL_POS / mapWid) + 0.5f;//MAP_WIDTH;
    nowTileIndexY = pos.y / MAP_HEIGHT;

    if (Input::GetButtonDown(VK_SPACE)) // TODO : �״� ���� ����, ���� �� �ٴ����� ���������� ����
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