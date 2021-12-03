#include "BattleScene.h"
#include "Image.h"
#include "PlayerTank.h"
#include "Tank.h"
#include "CommonFunction.h"
#include "EnemyTankFactory.h"
#include "EnemyTanks.h"
#include "AmmoManager.h"
#include "ItemManager.h"
#include "EnemyTankManager.h"
#include "UIManager.h"
#include "StageManager.h"
#include "ScoreManager.h"
#include "GameDataManager.h"


#define POS 8

HRESULT BattleScene::Init()
{
    SetWindowSize(300, 20, WIN_SIZE_X*4, WIN_SIZE_Y*4);
    windowX = WIN_SIZE_X , windowY = WIN_SIZE_Y;
    // 화면 비율 조정

    sampleImage = ImageManager::GetSingleton()->FindImage("Image/SamlpTile.bmp");
    // 맵 이미지 불러오기

    battleBackGround = ImageManager::GetSingleton()->FindImage("Image/background.bmp");
    // 배틀신 배경 불러오기

    grayBackGround1 = ImageManager::GetSingleton()->FindImage("Image/Title/GrayBackGround.bmp");
    grayBackGround2 = ImageManager::GetSingleton()->FindImage("Image/Title/GrayBackGround.bmp");
    stageNumImage = ImageManager::GetSingleton()->FindImage("Image/Text/Number1.bmp");
    stage = ImageManager::GetSingleton()->FindImage("Image/Text/Stage.bmp");
    entryScene1 = true;
    entryScene2 = false;
    stageRender = false;
    stageTime = 0.0f;
    grayPosY1 = ( 0 - (grayBackGround1->GetHeight() / 2));
    grayPosY2 = (WIN_SIZE_Y) + (grayBackGround2->GetHeight() / 2);

    waterCheck = false;
    waterTime = 0.0f;

    stageNum = GameDataManager::GetSingleton()->GetIsStage();
    Load(stageNum);
    
    if (GameDataManager::GetSingleton()->GetIsStage() != 1) {
        for (int y = 0; y < TILE_COUNT; y++) {
            for (int x = 0; x < TILE_COUNT; x++) {
                bufferTileInfo[y][x] = GameDataManager::GetSingleton()->GetTileInfo(y,x);
            }
        }
    }

    ScoreManager::GetSingleton()->Init();
    GameDataManager::GetSingleton()->SetPlayerIsDead(false);

    playerTank = new PlayerTank;
    playerTank->Init();

    enemyTankManager = new EnemyTankManager;
    enemyTankManager->Init();

    ammoManager = new AmmoManager;
    ammoManager->SetTileInfo(tileInfo);
    ammoManager->SetPlayerTank(playerTank);
    ammoManager->SetVecEnemyTank(enemyTankManager->GetVecEnemyTanks());
    ammoManager->Init();

    itemManager = new ItemManager;
    itemManager->Init();

    stageManager = new StageManager;
    stageManager->Init();

    uIManager = new UIManager;
    uIManager->Init();
 
    itemManager->Setdata(*playerTank, *enemyTankManager, tileInfo);
    playerTank->SetData(tileInfo, ammoManager, itemManager);
    enemyTankManager->SetData(tileInfo, *playerTank, ammoManager, itemManager);
    stageManager->SetData(enemyTankManager, playerTank, ammoManager, tileInfo);
    uIManager->SetData(playerTank, stageManager);


    stageManager->SetData(enemyTankManager, playerTank, ammoManager, tileInfo);

    ScoreManager::GetSingleton()->SetData(*playerTank, *enemyTankManager);

    return S_OK;
}

void BattleScene::Update()
{

    if (entryScene1) {
        if (!entryScene2) {
            grayPosY1 += 100 * TimerManager::GetSingleton()->GetDeltaTime();
            grayPosY2 -= 100 * TimerManager::GetSingleton()->GetDeltaTime();
            if (KeyManager::GetSingleton()->IsOnceKeyDown('Z')) {
                grayPosY1 = (WIN_SIZE_Y / 2) - (grayBackGround1->GetHeight() / 2);
                grayPosY2 = (WIN_SIZE_Y / 2) + (grayBackGround2->GetHeight() / 2);
            }
            if (grayPosY1 >= (WIN_SIZE_Y / 2) - (grayBackGround1->GetHeight() / 2)) {
                grayPosY1 = (WIN_SIZE_Y / 2) - (grayBackGround1->GetHeight() / 2);
                grayPosY2 = (WIN_SIZE_Y / 2) + (grayBackGround2->GetHeight() / 2);
                entryScene2 = true;
            }
        }
        else {
            if (stageTime < 2.0f) {
                stageTime += TimerManager::GetSingleton()->GetDeltaTime();
                if (KeyManager::GetSingleton()->IsOnceKeyDown('Z')) stageTime = 2.0f;
            }
            else {
                grayPosY1 -= 100 * TimerManager::GetSingleton()->GetDeltaTime();
                grayPosY2 += 100 * TimerManager::GetSingleton()->GetDeltaTime();
                if (KeyManager::GetSingleton()->IsOnceKeyDown('Z')) grayPosY1 = 0 - (grayBackGround1->GetHeight() / 2);
                if (grayPosY1 < 0 - (grayBackGround1->GetHeight() / 2)) {
                    entryScene1 = false;
                }
            }
        }
        return;
    }

    waterTime += TimerManager::GetSingleton()->GetDeltaTime();
    if (waterTime >= 0.4f) {
        waterTime = 0.0f;
        waterCheck = !waterCheck;
    }
    
    enemyTankManager->Update();
    playerTank->Update();
    ammoManager->Update();
    itemManager->Update();
    uIManager->Update();

    ScoreManager::GetSingleton()->Update(*playerTank, *enemyTankManager);
    stageManager->Update();
}

void BattleScene::Render(HDC hdc)
{
    if (entryScene1) {
        if (!entryScene2) {
            if (stageNum != 1) {
                battleBackGround->Render(hdc, battleBackGround->GetWidth() / 2, battleBackGround->GetHeight() / 2);
                for (int i = 0; i < TILE_COUNT; i++) {
                    for (int j = 0; j < TILE_COUNT; j++) {
                        for (int tileNumY = 0; tileNumY < 2; tileNumY++) {
                            for (int tileNumX = 0; tileNumX < 2; tileNumX++) {
                                if (bufferTileInfo[i][j].isDes[tileNumY][tileNumX]) {
                                    sampleImage->Render(hdc,
                                        bufferTileInfo[i][j].rc[tileNumY][tileNumX].left + (TILE_SIZE / 2),
                                        bufferTileInfo[i][j].rc[tileNumY][tileNumX].top + (TILE_SIZE / 2),
                                        bufferTileInfo[i][j].frameX[tileNumX],
                                        bufferTileInfo[i][j].frameY[tileNumY]);
                                }
                            }
                        }
                    }
                }
            }
            grayBackGround1->Render(hdc, WIN_SIZE_X / 2, grayPosY1);
            grayBackGround2->Render(hdc, WIN_SIZE_X / 2, grayPosY2);
        }
        else {
            if (stageTime < 2.0f) {
                grayBackGround1->Render(hdc, WIN_SIZE_X / 2, grayPosY1);
                grayBackGround2->Render(hdc, WIN_SIZE_X / 2, grayPosY2);
                stage->Render(hdc, (WIN_SIZE_X / 2) - 10, (WIN_SIZE_Y / 2));
                if (stageNum < 5) {
                    stageNumImage->Render(hdc, (WIN_SIZE_X / 2) + 17, (WIN_SIZE_Y / 2), stageNum, 0);
                } else if(stageNum < 10){
                    stageNumImage->Render(hdc, (WIN_SIZE_X / 2) + 17, (WIN_SIZE_Y / 2), stageNum - 5, 1);
                } else {
                    stageNumImage->Render(hdc, (WIN_SIZE_X / 2) + 17, (WIN_SIZE_Y / 2), 1, 0);
                    stageNumImage->Render(hdc, (WIN_SIZE_X / 2) + 24, (WIN_SIZE_Y / 2), 0, 0);
                }
            }
            else {
                battleBackGround->Render(hdc, battleBackGround->GetWidth() / 2, battleBackGround->GetHeight() / 2);
                for (int i = 0; i < TILE_COUNT; i++) {
                    for (int j = 0; j < TILE_COUNT; j++) {
                        for (int tileNumY = 0; tileNumY < 2; tileNumY++) {
                            for (int tileNumX = 0; tileNumX < 2; tileNumX++) {
                                if (tileInfo[i][j].isDes[tileNumY][tileNumX]) {
                                    sampleImage->Render(hdc,
                                        tileInfo[i][j].rc[tileNumY][tileNumX].left + (TILE_SIZE / 2),
                                        tileInfo[i][j].rc[tileNumY][tileNumX].top + (TILE_SIZE / 2),
                                        tileInfo[i][j].frameX[tileNumX],
                                        tileInfo[i][j].frameY[tileNumY]);
                                }
                            }
                        }
                    }
                }
                grayBackGround1->Render(hdc, WIN_SIZE_X / 2, grayPosY1);
                grayBackGround2->Render(hdc, WIN_SIZE_X / 2, grayPosY2);
            }
        }
        return;

    }


    battleBackGround->Render(hdc, battleBackGround->GetWidth() / 2, battleBackGround->GetHeight() / 2);
    for (int i = 0; i < TILE_COUNT; i++) {
        for (int j = 0; j < TILE_COUNT; j++) {

            if (tileInfo[i][j].isDes[0][0] == false && tileInfo[i][j].isDes[0][1] == false &&
                tileInfo[i][j].isDes[1][0] == false && tileInfo[i][j].isDes[1][1] == false)
                tileInfo[i][j].terrain = Terrain::Empty;

            for (int tileNumY = 0; tileNumY < 2; tileNumY++) {
                for (int tileNumX = 0; tileNumX < 2; tileNumX++) {
                    if (tileInfo[i][j].isDes[tileNumY][tileNumX]) {
                        if (tileInfo[i][j].terrain != Terrain::Forest)
                            sampleImage->Render(hdc,
                                tileInfo[i][j].rc[tileNumY][tileNumX].left + (TILE_SIZE / 2),
                                tileInfo[i][j].rc[tileNumY][tileNumX].top + (TILE_SIZE / 2),
                                tileInfo[i][j].frameX[tileNumX],
                                tileInfo[i][j].frameY[tileNumY]);
                        if (tileInfo[i][j].terrain == Terrain::Water) {
                            if (waterCheck) {
                                tileInfo[i][j].frameX[tileNumX] = 0 + tileNumX;
                                tileInfo[i][j].frameY[tileNumY] = 12 + tileNumY;
                            }
                            else {
                                tileInfo[i][j].frameX[tileNumX] = 4 + tileNumX;
                                tileInfo[i][j].frameY[tileNumY] = 12 + tileNumY;
                            }
                        }
                        if (KeyManager::GetSingleton()->IsStayKeyDown('0') && tileInfo[i][j].terrain != Terrain::Empty) {
                            Rectangle(hdc,
                                tileInfo[i][j].selectRc.left,
                                tileInfo[i][j].selectRc.top,
                                tileInfo[i][j].selectRc.right,
                                tileInfo[i][j].selectRc.bottom);
                        }
                        if (KeyManager::GetSingleton()->IsStayKeyDown('9')) {
                            if (tileInfo[i][j].terrain == Terrain::Brick) {
                                pen = (HPEN)CreateSolidBrush(RGB(185, 122, 87));
                            }
                            else if (tileInfo[i][j].terrain == Terrain::IronBrick) {
                                pen = (HPEN)CreateSolidBrush(RGB(195, 195, 195));
                            }
                            else if (tileInfo[i][j].terrain == Terrain::Water) {
                                pen = (HPEN)CreateSolidBrush(RGB(0, 162, 232));
                            }
                            else if (tileInfo[i][j].terrain == Terrain::Forest) {
                                pen = (HPEN)CreateSolidBrush(RGB(34, 177, 76));
                            }
                            else if (tileInfo[i][j].terrain == Terrain::Soild) {
                                pen = (HPEN)CreateSolidBrush(RGB(127, 127, 127));
                            }
                            else if (tileInfo[i][j].terrain == Terrain::Base) {
                                pen = (HPEN)CreateSolidBrush(RGB(200, 191, 231));
                            }
                            else if (tileInfo[i][j].terrain == Terrain::Empty) {
                                pen = (HPEN)CreateSolidBrush(RGB(30, 30, 30));
                            }
                            if (tileInfo[i][j].isDes[tileNumY][tileNumX] == false) pen = (HPEN)CreateSolidBrush(RGB(0, 0, 0));
                            oPen = (HPEN)SelectObject(hdc, pen);
                            Rectangle(hdc,
                                tileInfo[i][j].rc[tileNumY][tileNumX].left,
                                tileInfo[i][j].rc[tileNumY][tileNumX].top,
                                tileInfo[i][j].rc[tileNumY][tileNumX].right,
                                tileInfo[i][j].rc[tileNumY][tileNumX].bottom);
                            SelectObject(hdc, oPen);
                            DeleteObject(pen);
                        }

                    }
                }
            }
        }
    }
    // 숲타일 제외 모두 렌더

    enemyTankManager->Render(hdc);
    playerTank->Render(hdc);
    ammoManager->Render(hdc);

    uIManager->Render(hdc);
    for (int i = 0; i < TILE_COUNT; i++) {
        for (int j = 0; j < TILE_COUNT; j++) {
            for (int tileNumY = 0; tileNumY < 2; tileNumY++) {
                for (int tileNumX = 0; tileNumX < 2; tileNumX++) {
                    if (tileInfo[i][j].terrain == Terrain::Forest)
                    sampleImage->Render(hdc,
                        tileInfo[i][j].rc[tileNumY][tileNumX].left + (TILE_SIZE / 2),
                        tileInfo[i][j].rc[tileNumY][tileNumX].top + (TILE_SIZE / 2),
                        tileInfo[i][j].frameX[tileNumX],
                        tileInfo[i][j].frameY[tileNumY]);
                }
            }
        }
    }
    itemManager->Render(hdc);
    stageManager->Render(hdc);
    // 숲타일 렌더
}

void BattleScene::Release()
{
    SAFE_RELEASE(ammoManager);
    SAFE_RELEASE(playerTank);

    SAFE_RELEASE(enemyTankManager);
    SAFE_RELEASE(itemManager);
    SAFE_RELEASE(stageManager);
    SAFE_RELEASE(uIManager);
}

int BattleScene::Load(int num)
{
    {

        string loadFileName = "Save/saveMapData_" + to_string(num);

        loadFileName += ".map";

        HANDLE hFile = CreateFile(loadFileName.c_str(),
            GENERIC_READ,           // 읽기, 쓰기
            0, NULL,                // 공유, 보안 모드
            OPEN_EXISTING,          // 파일 만들거나 읽을 때 옵션
            FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등등)
            NULL);

        // 읽기
        DWORD readByte;
        if (ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_COUNT * TILE_COUNT,
            &readByte, NULL) == false)
        {
            MessageBox(g_hWnd, "맵 데이터 로드에 실패했습니다.", "에러", MB_OK);
        }

        CloseHandle(hFile);
        return num;
    }
}
