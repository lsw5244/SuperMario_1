#include "PlayerTank.h"
#include "Image.h"
#include "Config.h"
#include "EnemyTanks.h"
#include "AmmoManager.h"
#include "CommonFunction.h"
#include "ItemManager.h"
#include "ScoreManager.h"
#include "GameDataManager.h"

void PlayerTank::SetFrame()
{
    if (moveDir == MoveDir::Up) {
        if (elapsedCount == 0) elapsedCount = 1;
        else elapsedCount = 0;
    }
    if (moveDir == MoveDir::Left) {
        if (elapsedCount == 2) elapsedCount = 3;
        else elapsedCount = 2;
    }
    if (moveDir == MoveDir::Down) {
        if (elapsedCount == 4) elapsedCount = 5;
        else elapsedCount = 4;
    }
    if (moveDir == MoveDir::Right) {
        if (elapsedCount == 6) elapsedCount = 7;
        else elapsedCount = 6;
    }

}

void PlayerTank::CollisionAndMove(MoveDir movedir)
{
    RECT rc;
    RECT bufferRc;
    POINTFLOAT bufferPos;
    bool check = false;

    bufferRc = shape;
    bufferPos = pos;

    if (movedir == MoveDir::Left && isdead == false) {
        pos.x -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
    }
    else if (movedir == MoveDir::Right && isdead == false) {
        pos.x += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
    }
    else if (movedir == MoveDir::Up && isdead == false) {
        pos.y -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
    }
    else if (movedir == MoveDir::Down && isdead == false) {
        pos.y += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
    }

    shape.left = pos.x - 8;
    shape.top = pos.y - 8;
    shape.right = pos.x + 8;
    shape.bottom = pos.y + 8;

    for (int i = GetPosCount(pos.y, -2, false); i < GetPosCount(pos.y, 2, false); i++) {
        for (int j = GetPosCount(pos.x, -2, true); j < GetPosCount(pos.x, 2, true); j++) {
            if (!(tileInfo[i][j].terrain == Terrain::Empty || tileInfo[i][j].terrain == Terrain::Forest) && IntersectRect(&rc, &shape, &tileInfo[i][j].selectRc)) {
                check = true;
            }

            for (vector<EnemyTanks*>::iterator it = vecEnemyTank.begin();
                it != vecEnemyTank.end();
                it++)
            {
                RECT enemyRect = (*it)->GetRect();
                if (IntersectRect(&rc, &shape, &enemyRect)) check = true;

            }
        }
    }

    if (movedir == MoveDir::Left) {
        if (pos.x <= 16 + 8) check = true;
    }
    else if (movedir == MoveDir::Right) {
        if (pos.x >= 208 + 9) check = true;
    }
    else if (movedir == MoveDir::Up) {
        if (pos.y <= 16) check = true;
    }
    else if (movedir == MoveDir::Down) {
        if (pos.y >= 208 + 1) check = true;
    }
    if (check) {
        shape = bufferRc;
        pos = bufferPos;
    }
}

void PlayerTank::PosReset(MoveDir movedir)
{
    int posCount = 0;
    if (movedir == MoveDir::Left || movedir == MoveDir::Right) {
        int posY = ((int)pos.y - 8) % 8;
        for (float posNum = pos.y; posNum >= 8; posNum -= 8) posCount++;
        if (posY <= 3) {
            pos.y = (posCount - 1) * 8;
            pos.y += 8;
        }
        else {
            pos.y = (posCount - 1) * 8;
            pos.y += 16;
        }
    }
    else if (movedir == MoveDir::Up || movedir == MoveDir::Down) {
        int posX = ((int)pos.x - 16) % 8;
        for (float posNum = pos.x; posNum >= 8; posNum -= 8) posCount++;

        if (posX <= 3) {
            pos.x = (posCount - 1) * 8;
            pos.x += 8;
        }
        else {
            pos.x = (posCount - 1) * 8;
            pos.x += 16;
        }
    }
    shape.left = pos.x - 8;
    shape.top = pos.y - 8;
    shape.right = pos.x + 8;
    shape.bottom = pos.y + 8;
}

bool PlayerTank::SpawnEffect()
{
    spawnEffectTime += TimerManager::GetSingleton()->GetDeltaTime();

    if (spawnEffectTime >= 0.25)
    {
        if (spawnEffectCount != 12)
        {
            if (spawnEffectFrameX == 3)
            {
                spawnFrameUp = false;
            }
            else if (spawnEffectFrameX == 0)
            {
                spawnFrameUp = true;
            }
            switch (spawnFrameUp)
            {
            case true:
                spawnEffectFrameX++;
                break;
            case false:
                spawnEffectFrameX--;
                break;

            }
            spawnEffect->SetCurrFrameX(spawnEffectFrameX);

            spawnEffectCount++;
        }
        spawnEffectTime = 0;
    }

    if (spawnEffectCount == 12) return false;
    return true;
}

bool PlayerTank::ShieldEffect()
{
   if (shieldEffectTime < shieldEffectMaxTime)
   {
       shieldEffectTime += TimerManager::GetSingleton()->GetDeltaTime();
       shieldEffectDelay += TimerManager::GetSingleton()->GetDeltaTime();
       if (shieldEffectDelay < 0.1f)
       {
           return true;
       }
       if (shieldEffect->GetCurrFrameX() == 1)
       {
           shieldEffect->SetCurrFrameX(0);
       }
       else if (shieldEffect->GetCurrFrameX() == 0)
       {
           shieldEffect->SetCurrFrameX(1);
       }
       shieldEffectDelay = 0.0f;
       return true;
   } else {
       return false;
   }
}

HRESULT PlayerTank::Init()
{
    spawnEffect = ImageManager::GetSingleton()->FindImage("Image/Effect/Spawn_Effect.bmp");
    spawnEffectFrameX = 3;
    spawnEffectCount = 0;

    playerTank = ImageManager::GetSingleton()->FindImage("Image/Player/Player3.bmp");
    pos.x = 16 + 72;
    pos.y = WIN_SIZE_Y - 16;

    shieldEffect = ImageManager::GetSingleton()->FindImage("Image/Effect/Shield.bmp");
    shieldEffectDelay = 0.0f;

    deadEffect = ImageManager::GetSingleton()->FindImage("Image/Effect/EnemyTankBoom.bmp");
    deadEffecttime = 0.0f;
    deadEffectfreamX = 0;
    isdead = false;

    moveDir = MoveDir::Up;
    type = TankType::Player;

    Level = 0;
    moveSpeed = 50;
    maxAmmo = 1;
    shape.left = pos.x - 8;
    shape.top = pos.y - 8;
    shape.right = pos.x + 8;
    shape.bottom = pos.y + 8;

    loadDataCheck = true;
    isBarrier = false;
    fastAmmoReady = false;
    SuperPlayerMode = false;
    getItem = false;

    return S_OK;
}

void PlayerTank::Update()
{
    if (loadDataCheck) {
        LoadData();
        loadDataCheck = false;
    }
    if (life == 0) return;

    if (KeyManager::GetSingleton()->IsOnceKeyDown(SUPER_PLAYER_MODE))
    {
        SuperPlayerMode = !SuperPlayerMode;
        if (SuperPlayerMode) {
            for (int i = 0; i < 3; i++)LevelUp();
            moveSpeed = 150.0f;
        }
        else {
            moveSpeed = 50.0f;
            shieldEffectTime = 6.0f;
        }
    }
    if (SuperPlayerMode) {
        itemManager->ActiveShove();
        shieldEffectTime = 0;
    }

    RECT rc;
    if (SpawnEffect() == false)
    {
        if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
        {
            moveDir = MoveDir::Up;
            PosReset(MoveDir::Up);
            CollisionAndMove(MoveDir::Up);
            SetFrame();
        }
        else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN)) {
            moveDir = MoveDir::Down;
            PosReset(MoveDir::Down);
            CollisionAndMove(MoveDir::Down);
            SetFrame();
        }
        else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT)) {
            moveDir = MoveDir::Left;
            PosReset(MoveDir::Left);
            CollisionAndMove(MoveDir::Left);
            SetFrame();
        }
        else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT)) {
            moveDir = MoveDir::Right;
            PosReset(MoveDir::Right);
            CollisionAndMove(MoveDir::Right);
            SetFrame();
        }

        if (KeyManager::GetSingleton()->IsOnceKeyDown('Z'))
        {
            switch (moveDir)
            {
            case MoveDir::Left:
                ammoManager->Fire(moveDir, { (float)shape.left, pos.y }, type, fastAmmoReady, maxAmmo);
                break;
            case MoveDir::Right:
                ammoManager->Fire(moveDir, { (float)shape.right, pos.y }, type, fastAmmoReady, maxAmmo);
                break;
            case MoveDir::Up:
                ammoManager->Fire(moveDir, { pos.x, (float)shape.top }, type, fastAmmoReady, maxAmmo);
                break;
            case MoveDir::Down:
                ammoManager->Fire(moveDir, { pos.x, (float)shape.bottom }, type, fastAmmoReady, maxAmmo);
                break;
            }
        }
    }

    if (isdead == true)
    {
        deadEffecttime += TimerManager::GetSingleton()->GetDeltaTime();
        if (deadEffecttime >= 0.05)
        {
            deadEffectfreamX++;
            deadEffecttime = 0.0f;
            if (deadEffectfreamX >= 8)
            {
                if (life > 0)
                {
                    PlayerTankReset();
                }
            }
        }
   }
}

void PlayerTank::Render(HDC hdc)
{
    if (isdead == true)
    {
        if (deadEffectfreamX < 5)deadEffect->Render(hdc, pos.x, pos.y, deadEffectfreamX, 0);
        if (deadEffectfreamX == 5) deadEffect->Render(hdc, pos.x, pos.y, 3, 0);
        if (deadEffectfreamX == 6) deadEffect->Render(hdc, pos.x, pos.y, 2, 0);
        if (deadEffectfreamX == 7) deadEffect->Render(hdc, pos.x, pos.y, 1, 0);
        return;
    }
    if (life == 0) return;
    if (KeyManager::GetSingleton()->IsStayKeyDown(TANK_COLLIDER_DEBUG)) {
        Rectangle(hdc,
            shape.left,
            shape.top,
            shape.right,
            shape.bottom);
    }
    if (SpawnEffect() == false)
         {
               playerTank->Render(hdc, pos.x, pos.y, elapsedCount, Level);
         }
   else
        {
              spawnEffect->Render(hdc, pos.x, pos.y, spawnEffect->GetCurrFrameX(), 0);
        }
    if (ShieldEffect() == true && SpawnEffect() == false)
    {
       shieldEffect->Render(hdc, pos.x, pos.y, shieldEffect->GetCurrFrameX(), 0);
    }

}

void PlayerTank::Release()
{

}

void PlayerTank::LevelUp()
{
    if (Level < 3) Level++;
    if (Level == 1) {
        fastAmmoReady = true;
    }
    if (Level == 2) {
        maxAmmo = 2;
    }
    if (Level == 3) {
        ammoManager->PlayerAmmoPowerUp();
    }
}

void PlayerTank::PlayerTankReset()
{
    Level = 0;
    fastAmmoReady = false;
    deadEffectfreamX = 0;
    life--;
    pos.x = 16 + 72;
    pos.y = WIN_SIZE_Y - 16;
    isdead = false;
    spawnEffectTime = 0.0f;
    spawnEffectFrameX = 0;
    spawnEffectCount = 0;
    shieldEffectTime = 0.0f;
    shieldEffectDelay = 0.0f;
    maxAmmo = 1;
    ammoManager->PlayerAmmoPowerDown();

}

void PlayerTank::LoadData()
{
    life = GameDataManager::GetSingleton()->GetPlayerLife();
    for (int i = 0; i < GameDataManager::GetSingleton()->GetPlayerLevel(); i++) LevelUp();
}

void PlayerTank::SetData(TILE_INFO(*tileInfo)[TILE_COUNT], AmmoManager* ammoManager, ItemManager* itemManager)
{
    this->tileInfo = tileInfo;
    this->ammoManager = ammoManager;
    this->itemManager = itemManager;
}

