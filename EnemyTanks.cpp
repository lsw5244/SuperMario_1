#include "EnemyTanks.h"
#include "CommonFunction.h"

void EnemyTanks::CollisionAndMove(MoveDir movedir)
{
    RECT rc;
    RECT bufferRc;
    POINTFLOAT bufferPos;
    bool check = false;
    bool tankCheck = false;

    bufferRc = shape;
    bufferPos = pos;
    if (movedir == MoveDir::Left) {
        pos.x -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
    }
    else if (movedir == MoveDir::Right) {
        pos.x += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
    }
    else if (movedir == MoveDir::Up) {
        pos.y -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
    }
    else if (movedir == MoveDir::Down) {
        pos.y += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
    }
    shape.left = pos.x - 8;
    shape.top = pos.y - 8;
    shape.right = pos.x + 8;
    shape.bottom = pos.y + 8;

    for (int i = GetPosCount(pos.y, -2, false); i < GetPosCount(pos.y, 2, false); i++) {
        for (int j = GetPosCount(pos.x, -2, true); j < GetPosCount(pos.x, 2, true); j++) {
            if ((!(tileInfo[i][j].terrain == Terrain::Empty || tileInfo[i][j].terrain == Terrain::Forest)) && 
                IntersectRect(&rc, &shape, &tileInfo[i][j].selectRc)) {
                check = true;
            }
        }
    }
    // 해당 타일이 비어있거나 숲타일일 경우

    if (!spawnColl) if (IntersectRect(&rc, playerRect, &shape))check = true;
    // 스폰시 플레이어와 충돌할 경우

    for (vector<EnemyTanks*>::iterator it = vecEnemyTanks.begin();
        it != vecEnemyTanks.end(); it++)
    {
        RECT enemyRect = (*it)->GetRect();
        if (this != (*it)) {
            if (IntersectRect(&rc, &shape, &enemyRect)) {
                if (!spawnColl)tankCheck = true;
            }
        }
    }
    // 자신을 제외한 다른 플레이어와 충돌 체크


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
    if (check || tankCheck) {
        shape = bufferRc;
        pos = bufferPos;
    }
}

void EnemyTanks::PosReset(MoveDir movedir)
{
    bool tankCheck = false;
    int posCount = 0;
    POINTFLOAT bufferPos = pos;
    RECT bufferRc = shape;
    RECT rc;
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

    for (vector<EnemyTanks*>::iterator it = vecEnemyTanks.begin();
        it != vecEnemyTanks.end();
        it++)
    {
        RECT enemyRect = (*it)->GetRect();
        if (this != (*it)) {
            if (IntersectRect(&rc, &shape, &enemyRect)) {
                if (!spawnColl)tankCheck = true;
            }
        }
    }
    
    if (IntersectRect(&rc, playerRect, &shape)|| tankCheck) {
        shape = bufferRc;
        pos = bufferPos;
    }
}

void EnemyTanks::TankUpdate()
{

    if (spawnColl) {
        bool check = true;
        RECT rc;
        for (vector<EnemyTanks*>::iterator it = vecEnemyTanks.begin();
            it != vecEnemyTanks.end();
            it++)
        {
            RECT enemyRect = (*it)->GetRect();
            if (this != (*it)) {
                if (IntersectRect(&rc, &shape, &enemyRect)) check = false;
            }
        }
        if (IntersectRect(&rc, playerRect, &shape)) check = false;
        if (check) spawnColl = false;
    }

    time += TimerManager::GetSingleton()->GetDeltaTime();
    if (time >= 0.3f) {
        tuple<MoveDir, bool> result = AutoMove(movedir, pos);
        if (get<0>(result) == movedir && get<1>(result)) {
            time = 0;
        }
        else if (get<0>(result) != movedir && !get<1>(result)) {
            movedir = get<0>(result);
            time = 0;
        }
    }

    switch (movedir) {
    case MoveDir::Up:
        PosReset(MoveDir::Up);
        CollisionAndMove(MoveDir::Up);
        elapsedWay = 0;
        elapsedCount++;
        elapsedCount = CurrFrame(*img, &elapsedCount, 1);
        break;
    case MoveDir::Down:
        PosReset(MoveDir::Down);
        CollisionAndMove(MoveDir::Down);
        elapsedWay = 4;
        elapsedCount++;
        elapsedCount = CurrFrame(*img, &elapsedCount, 5);
        break;
    case MoveDir::Right:
        PosReset(MoveDir::Right);
        CollisionAndMove(MoveDir::Right);
        elapsedWay = 6;
        elapsedCount++;
        elapsedCount = CurrFrame(*img, &elapsedCount, 3);
        break;
    case MoveDir::Left:
        PosReset(MoveDir::Left);
        CollisionAndMove(MoveDir::Left);
        elapsedWay = 2;
        elapsedCount++;
        elapsedCount = CurrFrame(*img, &elapsedCount, 7);
        break;
    }


}

int EnemyTanks::itemTankImg(int num)
{
    itemTime += TimerManager::GetSingleton()->GetDeltaTime();
    if (itemTime >= 0.1f) {
        itemTime = 0.0f;
        if (itemfraemY == num) {
            itemfraemY++;
        } else {
            itemfraemY = num;
        }
    }
    return itemfraemY;
}

int EnemyTanks::CurrFrame(Image enemyTank, int* elapsedCount, int setCurr)
{
    if (*elapsedCount == 2)
    {
        if (enemyTank.GetCurrFrameX() % 2 == 0)
        {
            enemyTank.SetCurrFrameX(setCurr);
        }
        else if (enemyTank.GetCurrFrameX() % 2 != 0)
        {
            enemyTank.SetCurrFrameX(setCurr - 1);
        }
        return 0;
    }
    return *elapsedCount;
}

tuple<MoveDir, bool> EnemyTanks::AutoMove(MoveDir moveDir, POINTFLOAT pos)
{
    int randomValue = rand() % 7;
    RECT rc;
    RECT bufferRc1 = shape;
    RECT bufferRc2 = shape;
    RECT bufferRc3 = shape;
    POINTFLOAT bufferPos1 = pos;
    POINTFLOAT bufferPos2 = pos;
    POINTFLOAT bufferPos3 = pos;
    bool check1 = true;
    bool check2 = true;
    bool check3 = true;

    if (moveDir == MoveDir::Up || moveDir == MoveDir::Down) {
        if (moveDir == MoveDir::Up) {
            bufferPos3.y -= 1;
            bufferRc3.top = bufferPos3.y - 9;
            bufferRc3.left = bufferPos3.x - 7;
            bufferRc3.bottom = bufferPos3.y + 9;
            bufferRc3.right = bufferPos3.x + 7;
        }
        if (moveDir == MoveDir::Down) {
            bufferPos3.y += 1;
            bufferRc3.top = bufferPos3.y - 9;
            bufferRc3.left = bufferPos3.x - 7;
            bufferRc3.bottom = bufferPos3.y + 9;
            bufferRc3.right = bufferPos3.x + 7;
        }
        bufferPos1.x -= 1;
        bufferPos2.x += 1;
        bufferRc1.top = bufferPos1.y - 7;
        bufferRc1.left = bufferPos1.x - 9;
        bufferRc1.bottom = bufferPos1.y + 7;
        bufferRc1.right = bufferPos1.x + 9;

        bufferRc2.top = bufferPos2.y - 7;
        bufferRc2.left = bufferPos2.x - 9;
        bufferRc2.bottom = bufferPos2.y + 7;
        bufferRc2.right = bufferPos2.x + 9;
    }
    else if (moveDir == MoveDir::Right || moveDir == MoveDir::Left) {
        if (moveDir == MoveDir::Left) {
            bufferPos3.x -= 1;
            bufferRc3.top = bufferPos3.y - 7;
            bufferRc3.left = bufferPos3.x - 9;
            bufferRc3.bottom = bufferPos3.y + 7;
            bufferRc3.right = bufferPos3.x + 9;
        }
        if (moveDir == MoveDir::Right) {
            bufferPos3.x += 1;
            bufferRc3.top = bufferPos3.y - 7;
            bufferRc3.left = bufferPos3.x - 9;
            bufferRc3.bottom = bufferPos3.y + 7;
            bufferRc3.right = bufferPos3.x + 9;
        }
        bufferPos1.y -= 1;
        bufferPos2.y += 1;
        bufferRc1.top = (bufferPos1.y - 1) - 8;
        bufferRc1.left = bufferPos1.x - 7;
        bufferRc1.bottom = (bufferPos1.y - 1) + 8;
        bufferRc1.right = bufferPos1.x + 7;

        bufferRc2.top = (bufferPos2.y + 1) - 8;
        bufferRc2.left = bufferPos2.x - 7;
        bufferRc2.bottom = (bufferPos2.y + 1) + 8;
        bufferRc2.right = bufferPos2.x + 7;
    }

    for (int i = GetPosCount(pos.y, -2, false); i < GetPosCount(pos.y, 2, false); i++) {
        for (int j = GetPosCount(pos.x, -2, true); j < GetPosCount(pos.x, 2, true); j++) {
            if (!(tileInfo[i][j].terrain == Terrain::Empty || tileInfo[i][j].terrain == Terrain::Forest) && IntersectRect(&rc, &bufferRc1, &tileInfo[i][j].selectRc)) {
                check1 = false;
            }
            if (!(tileInfo[i][j].terrain == Terrain::Empty || tileInfo[i][j].terrain == Terrain::Forest) && IntersectRect(&rc, &bufferRc2, &tileInfo[i][j].selectRc)) {
                check2 = false;
            }
            if (!(tileInfo[i][j].terrain == Terrain::Empty || tileInfo[i][j].terrain == Terrain::Forest) && IntersectRect(&rc, &bufferRc3, &tileInfo[i][j].selectRc)) {
                check3 = false;
            }
        }
    }
    if (movedir == MoveDir::Left) {
        if (bufferPos3.x <= 16 + 8) check3 = false;
    }
    else if (movedir == MoveDir::Right) {
        if (bufferPos3.x >= 208 + 9) check3 = false;
    }
    else if (movedir == MoveDir::Up) {
        if (bufferPos3.y <= 16) check3 = false;
    }
    else if (movedir == MoveDir::Down) {
        if (bufferPos3.y >= 208 + 1) check3 = false;
    }

    if (!spawnColl) if(IntersectRect(&rc, playerRect, &bufferRc3))check3 = false;
    for (int i = 0; i < 4; i++) {
        for (vector<EnemyTanks*>::iterator it = vecEnemyTanks.begin();
            it != vecEnemyTanks.end();
            it++)
        {
            RECT enemyRect = (*it)->GetRect();
            if ((*it)==this) continue;
            if (IntersectRect(&rc, &bufferRc3, &enemyRect)) {
                if (!spawnColl)check3 = false;
            }
        }
    }

    if (moveDir == MoveDir::Left || moveDir == MoveDir::Right) {
        if (bufferPos1.y <= 16) check1 = false;
        if (bufferPos2.y >= 208 + 1) check2 = false;
    }
    else if (moveDir == MoveDir::Up || moveDir == MoveDir::Down) {
        if (bufferPos1.x <= 16 + 8) check1 = false;
        if (bufferPos2.x >= 208 + 9) check2 = false;
    }

    if (check1 || check2) {
        if (moveDir == MoveDir::Up || moveDir == MoveDir::Down) {
            if (randomValue >= 2 && check3) {
                return tuple<MoveDir, bool>(moveDir, true);
            }

            if (check1 && check2) {
                if (randomValue == 0) {
                    return  tuple<MoveDir, bool>(MoveDir::Right, false);
                }
                else if (randomValue == 1) {
                    return tuple<MoveDir, bool>(MoveDir::Left, false);
                }
            }
            else {
                if (check1) return tuple<MoveDir, bool>(MoveDir::Left, false);
                if (check2) return tuple<MoveDir, bool>(MoveDir::Right, false);
            }
        }
        else if (moveDir == MoveDir::Right || moveDir == MoveDir::Left) {
            if (randomValue >= 2 && check3) {
                return tuple<MoveDir, bool>(moveDir, true);
            }

            if (check1 && check2) {
                if (randomValue == 0) {
                    return tuple<MoveDir, bool>(MoveDir::Up, false);
                }
                else if (randomValue == 1) {
                    return tuple<MoveDir, bool>(MoveDir::Down, false);
                }
                else {
                    return tuple<MoveDir, bool>(moveDir, false);
                }
            }
            else {
                if (check1) return tuple<MoveDir, bool>(MoveDir::Up, false);
                if (check2) return tuple<MoveDir, bool>(MoveDir::Down, false);
            }
        }
    }
    else {
        if (!check3) {
            if (moveDir == MoveDir::Up && randomValue >= 3) return tuple<MoveDir, bool>(MoveDir::Down, false);
            if (moveDir == MoveDir::Down && randomValue >= 3) return tuple<MoveDir, bool>(MoveDir::Up, false);
        }

        if (!check3) {
            if (moveDir == MoveDir::Right && randomValue >= 3) return tuple<MoveDir, bool>(MoveDir::Left, false);
            if (moveDir == MoveDir::Left && randomValue >= 3) return tuple<MoveDir, bool>(MoveDir::Right, false);
        }
    }
    return tuple<MoveDir, bool>(moveDir, false);
}

HRESULT EnemyTanks::TankInit(int posX, bool item)
{
    destructionEffect1 = ImageManager::GetSingleton()->FindImage("Image/Effect/EnemyTankBoom.bmp");
    pointImage = ImageManager::GetSingleton()->FindImage("Image/Icon/Point.bmp");
    isItemDes = false;
    destructionEffectTime = 0;
    timeStop = false;
    itemTank = item;
    spawnColl = true;
    movedir = MoveDir::Down;
    elapsedCount = 0;
    elapsedWay = 0;
    boomItemCheck = false;

    if (posX == 1) {
        pos.x = 16 + (8);
    }
    else if (posX == 2) {
        pos.x = 16 + (8 + 96);
    }
    else {
        pos.x = 16 + (8 + 192);
    }
    pos.y = 16;

    shape.left = pos.x - 8;
    shape.top = pos.y - 8;
    shape.right = pos.x + 8;
    shape.bottom = pos.y + 8;

    isDestruction = false;
    isDestructionEffect = false;
    destructionEffectNum = 0;
    hp = 1;
    return S_OK;
}
