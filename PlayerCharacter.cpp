#include "PlayerCharacter.h"
#include "Image.h"
#include "Input.h"
#include "MacroCollection.h"
#include "GameDataContainer.h"

void PlayerCharacter::UpdateCollider()
{
    SetRect(&collider, pos.x - img->GetFrameWidth() / 2,
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

void PlayerCharacter::AnimationFrameChanger()
{
    // 14 * 2
    /*
    FrameX                              FrameY
    0. �� �ֱ�                           0. ������ �ٶ󺸱�
    1. �޸��� 1                          1. ���� �ٶ󺸱�
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

    // �ɾ��ֱ�
    if (Input::GetButtonDown(VK_DOWN))
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
    if (Input::GetButtonDown('X'))
    {
        frameX = 11;
    }

    // ��� ���
}

HRESULT PlayerCharacter::Init()
{
    img = ImageManager::GetInstance()->FindImage("Image/Character/SamllRedMario.bmp");

    pos.x = 32;//WIN_SIZE_X / 2;
    pos.y = WIN_SIZE_Y / 2;

    UpdateCollider();

    return S_OK;
}

void PlayerCharacter::Update()
{
    nowTileIndexX = (pos.x + GLOBAL_POS) / TILE_SIZE;
    nowTileIndexY = pos.y / MAP_HEIGHT;

    cout << "x : " << nowTileIndexX << endl;
    cout << "y : " << nowTileIndexY << endl;

    //cout << OnCollisionEnter(collider, TILE_DATA[nowTileIndexY + 1][nowTileIndexX].rc) << endl;

    UpdateCollider();

    if (isDead == true)
        return;

    if (Input::GetButtonDown(VK_SPACE)) // TODO : �״� ���� ����, ���� �� �ٴ����� ���������� ����
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


    // 1. �Ʒ� ���� collider �־�� ��
    // 2. ���� pos.y�� ���� ���� bottom���� �۾ƾ� ��
    // 3. TODO : ���� �� �־�� ��
    
    // �ٴ� �ݶ��̴� (�Ʒ�)
    if (TILE_DATA[nowTileIndexY + 1][nowTileIndexX].isCollider == true
        && OnCollisionEnter(collider, TILE_DATA[nowTileIndexY + 1][nowTileIndexX].rc) == true
        /*pos.y < TILE_DATA[nowTileIndexY][nowTileIndexX].rc.bottom*/)
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
    // TODO : ���� �ִ���� �����ϱ� 
    // TODO : �Ӹ� �� �ݶ��̴� �����ϱ�
    if (Input::GetButton('Z') && jumpEnd == false)
    {
        isGround = false;
        currJumpPower += jumpPower;
        if (TILE_DATA[nowTileIndexY - 1][nowTileIndexX].isCollider == true &&
            pos.y > TILE_DATA[nowTileIndexY][nowTileIndexX].rc.top
            )
        {
            jumpEnd = true;
            currJumpPower = 0.0f;
        }

        // ���� �ִ����
        if (currJumpPower >= maxJumpPower)
        {
            jumpEnd = true;
        }
        currJumpPower = min(currJumpPower, maxJumpPower);

        //// ���� ������ ���� ( �ִ� ���� ����, �Ӹ��� ���� �΋H��)
        //if (TILE_DATA[nowTileIndexY - 1][nowTileIndexX].isCollider == true &&
        //    pos.y < TILE_DATA[nowTileIndexY][nowTileIndexX].rc.top
        //    )
        //{
        //    jumpEnd = true;
        //    currJumpPower = 0.0;
        //}
    }

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
        gravity += gravityAcceleration;
        gravity = min(gravity, maxGravity);
        //cout << gravity << endl;
    }

    AnimationFrameChanger();

    if (pos.x + currSpeed > 0 && pos.x + currSpeed < WIN_SIZE_X / 2 
        /*&& OnCollisionEnter(collider, TILE_DATA[nowTileIndexY][nowTileIndexX + 1].rc) == true*/)
    {
        pos.x += currSpeed;
    }
    else
    {
        if (currSpeed > 0)  // ���� �� ���� globalPos ����
        {
            GameDataContainer::GetInstance()->SetGlobalPos(GLOBAL_POS + currSpeed);
        }
    }

    //if ()
    {
       pos.y -= currJumpPower;
    }
}

void PlayerCharacter::Render(HDC hdc)
{

    Rectangle(hdc, collider.left, collider.top, collider.right, collider.bottom);
    img->Render(hdc, (int)pos.x, (int)pos.y, frameX, frameY);

    if (Input::GetButton(VK_RBUTTON))
    {
        TILE_DATA[nowTileIndexY - 1][nowTileIndexX];

        Rectangle(hdc, TILE_DATA[nowTileIndexY - 1][nowTileIndexX].rc.left
            , TILE_DATA[nowTileIndexY - 1][nowTileIndexX].rc.top
            , TILE_DATA[nowTileIndexY - 1][nowTileIndexX].rc.right
            , TILE_DATA[nowTileIndexY - 1][nowTileIndexX].rc.bottom);

        Rectangle(hdc, TILE_DATA[nowTileIndexY + 1][nowTileIndexX].rc.left
            , TILE_DATA[nowTileIndexY + 1][nowTileIndexX].rc.top
            , TILE_DATA[nowTileIndexY + 1][nowTileIndexX].rc.right
            , TILE_DATA[nowTileIndexY + 1][nowTileIndexX].rc.bottom);

    }

    cout << GLOBAL_POS << endl;
}

void PlayerCharacter::Release()
{
}
