#include "PlayerCharacter.h"
#include "Image.h"
#include "Input.h"
#include "MacroCollection.h"
#include "GameDataContainer.h"

void PlayerCharacter::UpdateCollider()
{
    SetRect(&collider, (int)pos.x - img->GetFrameWidth() / 2,
        (int)pos.y - (img->GetFrameWidth() * min(level - 1 , 1)),  // ������ ������ top�� ��ġ�� �����
        (int)pos.x + img->GetFrameWidth() / 2,
        (int)pos.y + img->GetFrameHeight() / 2);
}

bool PlayerCharacter::OnCollisionEnter(RECT plyaerRect, RECT tileRect)
{
    if (plyaerRect.left > tileRect.right - GLOBAL_POS)	return false;
    if (plyaerRect.right < tileRect.left - GLOBAL_POS)	return false;
    if (plyaerRect.top > tileRect.bottom)	return false;
    if (plyaerRect.bottom < tileRect.top)	return false;

    return true;
}

void PlayerCharacter::Jump()
{
    // �����ϴ� �Ӹ� �ھ��� �� ó��
    if (isGround == false &&
        TILE_DATA[nowTileIndexY - min(level, 2)][nowTileIndexX].isCollider == true &&
        OnCollisionEnter(collider, TILE_DATA[nowTileIndexY - min(level, 2)][nowTileIndexX].rc))
    {
        jumpEnd = true;
        currJumpPower *= -1.0f;
        CheckBlockTypeAndCallItemManager(TILE_DATA[nowTileIndexY - min(level, 2)][nowTileIndexX]);
    }

    if (isGround == false)
    {
        currJumpPower -= gravity * DELETA_TIME;
        gravity += gravityAcceleration * DELETA_TIME;
        gravity = min(gravity, maxGravity);
        //return;
    }

    if (TILE_DATA[nowTileIndexY + 1][nowTileIndexX].isCollider == true &&
        OnCollisionEnter(collider, TILE_DATA[nowTileIndexY + 1][nowTileIndexX].rc)
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
    //if (isGround)
    {
        if (Input::GetButton(VK_RIGHT))
        {
            currSpeed += (acceleration - (jumpCorrectionSpeed * !isGround)) * DELETA_TIME;
            //currSpeed += acceleration * DELETA_TIME;
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

void PlayerCharacter::Attack()
{
    if (Input::GetButtonDown('X') && level >= 3 && isAttacking == false)
    {
        if (AMMO_MANAGER->PlayerFire(pos, (MoveDirection)frameY) == false) // �Ѿ� ���� ��
        {
            return;
        }
        isAttacking = true;
        ChangeAnimationFrame(PlayerAnimation::Attack, frameY);
        elapsedTime = 0.0f;
    }

    if (isAttacking == true) // ���� �ִϸ��̼�
    {
        elapsedTime += DELETA_TIME;
        if (elapsedTime > 0.1f)
        {
            isAttacking = false;
            elapsedTime = 0.0f;
        }
    }
}

void PlayerCharacter::UpdatePosition()
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

void PlayerCharacter::ChangeAnimationFrame()
{
    // ���� �ִϸ��̼�
    if (currSpeed < 0)
    {
        frameY = (int)MoveDirection::Left;
    }
    else if (currSpeed > 0)
    {
        frameY = (int)MoveDirection::Right;
    }
    
    // �����ϱ�
    if (isAttacking == true)
    {
        ChangeAnimationFrame(PlayerAnimation::Attack, frameY);
        return;
    }

    // �� �ִ� �ִϸ��̼�
    if (currSpeed == 0)
    {
        ChangeAnimationFrame(PlayerAnimation::Idle, frameY);
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
                ChangeAnimationFrame(++frameX, frameY);
                break;
            case PlayerAnimation::Run3:
            default:
                ChangeAnimationFrame(PlayerAnimation::Run1, frameY);
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
        ChangeAnimationFrame(PlayerAnimation::Jump, frameY);
        return;
    }

    // ������ȯ �ִϸ��̼�
    if (currSpeed > 0) // ������ ���� ���ε�
    {
        if (Input::GetButton(VK_LEFT))
        {
            ChangeAnimationFrame(PlayerAnimation::ChangeDirection, frameY);
            return;
        }
    }
    if (currSpeed < 0)
    {
        if (Input::GetButton(VK_RIGHT))
        {
            ChangeAnimationFrame(PlayerAnimation::ChangeDirection, frameY);
            return;
        }
    }

    // �ɾ��ֱ�
    if (Input::GetButton(VK_DOWN))
    {
        if (level != 1)
        {
            ChangeAnimationFrame(PlayerAnimation::Sit, frameY);
        }
    }

    //// �ױ�
    //if (isDead == true)
    //{
    //    ChangeAnimationFrame(PlayerAnimation::Die, frameY);
    //}

    // ��� ���
}

void PlayerCharacter::ChangeAnimationFrame(int frameX, int frameY)
{
    this->frameX = frameX;
    this->frameY = frameY;
}

void PlayerCharacter::CheckBlockTypeAndCallItemManager(TILE& hitTile)
{
    // 1�� �� ������ ������ ���ÿ� �������� �Դ� ���� �����ϱ� ����
    POINTFLOAT spawnPos = { (float)hitTile.rc.left + TILE_SIZE / 2 - GLOBAL_POS,
        (float)hitTile.rc.top + TILE_SIZE / 2 - 1 };

    if (hitTile.type == BlockType::ItemBlock)
    {
        ITEM_MANAGER->SpawnItem(spawnPos);

        // ������ ���� ������ �ٲٱ�
        hitTile.type = BlockType::CanDestroyBrick;
        hitTile.frameX = 10;
        hitTile.frameY = 6;
    }
    if (hitTile.type == BlockType::CoinBlock || hitTile.type == BlockType::HiddenCoinBlcok)
    {
        ITEM_MANAGER->SpawnCoin(spawnPos);
        hitTile.type = BlockType::CanDestroyBrick;
        hitTile.frameX = 10;
        hitTile.frameY = 6;
    }
}

void PlayerCharacter::CheckCatchFlag()
{
    /*Flag, FlagPole, FlagTop,*/
    if (TILE_DATA[nowTileIndexY][nowTileIndexX].type == BlockType::Flag ||
        TILE_DATA[nowTileIndexY][nowTileIndexX].type == BlockType::FlagPole ||
        TILE_DATA[nowTileIndexY][nowTileIndexX].type == BlockType::FlagTop)
    {
        isClear = true;
        elapsedTime = 0.0f;
        ChangeAnimationFrame(PlayerAnimation::Flag1, frameY);
    }
}

void PlayerCharacter::CheckIsDead()
{
    if (pos.y > WIN_SIZE_Y || level < 1)
    {
        isDead = true;
    }
}


HRESULT PlayerCharacter::Init()
{
    img = ImageManager::GetInstance()->FindImage("Image/SamllRedMario.bmp");
    isGround = true;
    isDead = false;

    pos.x = WIN_SIZE_X / 2;
    pos.y = WIN_SIZE_Y / 2;

    UpdateCollider();

    return S_OK;
}

void PlayerCharacter::Update()
{
    //cout << level << endl;
    //cout << elapsedTime << endl;
    if (Input::GetButtonDown('G') && level < 3)
    {
        elapsedTime = 0.0f;
        level++;
        isGrowing = true;
    }

    if (Input::GetButtonDown('S'))
    {
        POINTFLOAT temp = { (float)TILE_DATA[nowTileIndexY - min(level, 2)][nowTileIndexX].rc.left + TILE_SIZE / 2 ,
         (float)TILE_DATA[nowTileIndexY - min(level, 2)][nowTileIndexX].rc.top + TILE_SIZE / 2 };
        ITEM_MANAGER->SpawnItem(temp);
    }

    //if (Input::GetButtonDown('H') && isSmalling == false)
    //{

    //    return;
    //}
/*--------------------------*/
    if (isDead == true)
    {
        DeadAnimation();
        return;
    }

    if (isClear == true)
    {
        ClearAnimation();
        return;
    }

    if (isGrowing == true)
    {
        GrowAnimation();
        return;
    }

    if (isSmalling == true)
    {
        SmallingAnimation();
        return;
    }

    Attack();

    Jump();

    Move();

    ChangeAnimationFrame();

    UpdatePosition();

    CheckCatchFlag();

    CheckIsDead();

    nowTileIndexX = (int)(pos.x + GLOBAL_POS) / INGAME_RENDER_TILE_WIDHT_COUNT;
    nowTileIndexY = (int)pos.y / MAP_HEIGHT;

    UpdateCollider();
}

void PlayerCharacter::Render(HDC hdc)
{
    //���� �ݶ��̴�
    Rectangle(hdc, collider.left, collider.top, collider.right, collider.bottom);

    // ���� ��ġ Ÿ��
    //Rectangle(hdc, TILE_DATA[nowTileIndexY][nowTileIndexX].rc.left - GLOBAL_POS,
    //    TILE_DATA[nowTileIndexY][nowTileIndexX].rc.top,
    //    TILE_DATA[nowTileIndexY][nowTileIndexX].rc.right - GLOBAL_POS,
    //    TILE_DATA[nowTileIndexY][nowTileIndexX].rc.bottom);

    img->Render(hdc, pos.x, pos.y, frameX, frameY);

    //pos��ġ
    Rectangle(hdc, (int)pos.x - 1, (int)pos.y - 1, (int)pos.x + 1, (int)pos.y + 1);
}

void PlayerCharacter::Release()
{
}

void PlayerCharacter::GrowAnimation()
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
                ChangeAnimationFrame(PlayerAnimation::Grow1, frameY);
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

void PlayerCharacter::SmallingAnimation()
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
            ChangeAnimationFrame(PlayerAnimation::Grow1, frameY);
            break;
        }
        elapsedTime = 0.0f;
    }
}

void PlayerCharacter::ClearAnimation()
{
    static bool landFloor = false;

    elapsedTime += DELETA_TIME;

    if (landFloor == true)
    {
        if (elapsedTime > 2.0f)
        {
            landFloor = false;
            SceneManager::GetInstance()->ChangeScene("ClearScene");
        }
        return;
    }

    nowTileIndexX = (int)(pos.x + GLOBAL_POS) / INGAME_RENDER_TILE_WIDHT_COUNT;
    nowTileIndexY = (int)pos.y / MAP_HEIGHT;

    if (elapsedTime > 0.15f)
    {
        if (frameX == PlayerAnimation::Flag1)
        {
            ChangeAnimationFrame(PlayerAnimation::Flag2, frameY);
        }
        else
        {
            ChangeAnimationFrame(PlayerAnimation::Flag1, frameY);
        }
        elapsedTime = 0.0f;
    }

    // �ٴڿ� ���� �� ���� ��������
    if (!(TILE_DATA[nowTileIndexY + 1][nowTileIndexX].isCollider == true &&
        TILE_DATA[nowTileIndexY + 1][nowTileIndexX].rc.top < collider.bottom))
    {
        pos.y += 50.0f * DELETA_TIME;
    }
    else // �� �������� ��
    {
        elapsedTime = 0.0f;
        landFloor = true;
    }

    UpdateCollider();
}

void PlayerCharacter::DeadAnimation()
{
    elapsedTime += DELETA_TIME;
    ChangeAnimationFrame(PlayerAnimation::Die, frameY);
    if (elapsedTime > 1.0f)
    {
        SceneManager::GetInstance()->ChangeScene("DeadScene");
    }

}

void PlayerCharacter::Hit()
{
    // 1 : small, 2 :  big, 3 : fire

    if (level < 1)
    {
        isDead = true;
        ChangeAnimationFrame();
        return;
    }

    if (level < 3)
    {
        level = 1;
        isSmalling = true;
    }
}

void PlayerCharacter::GetDamage()
{
    if (isSmalling == true || isGrowing == true)
        return;

    elapsedTime = 0.0f;
    --level;
    Hit();
}

void PlayerCharacter::LevelUp()
{
    elapsedTime = 0.0f;
    level++;
    isGrowing = true;
}

void PlayerCharacter::AddJumpower(float power)
{
    isGround = false;
    gravity = 0.0f;// *DELETA_TIME;
    currJumpPower += power;
}
