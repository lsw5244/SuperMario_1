#include "GameScene.h"
#include "CommonFunction.h"
#include "Image.h"
#include "Input.h"
#include "GameDataContainer.h"
#include "AmmoManager.h"

HRESULT GameScene::Init()
{
    SetWindowSize(300, 20, GAME_SCENE_WIN_SIZE_X, GAME_SCENE_WIN_SIZE_Y);

    GameDataContainer::GetInstance()->SetGlobalPos(0);

    mapSpriteImg = ImageManager::GetInstance()->FindImage("Image/mario_overwordTile.bmp");
    Load();
    GameDataContainer::GetInstance()->SetMap(map);
    
    mario = new PlayerCharacter;
    mario->SetPos({ WIN_SIZE_X / 3, WIN_SIZE_Y / 2 });
    GameDataContainer::GetInstance()->SetPlayer(mario);

    mushroom.Init();
    mushroom.SetPos({ WIN_SIZE_X / 2, WIN_SIZE_Y / 2 });

    ammoManger.Init();
    GameDataContainer::GetInstance()->SetAmmoManager(&ammoManger);

    itemManager.Init();
    GameDataContainer::GetInstance()->SetItemManager(&itemManager);

    monsterManager.Init();

    return S_OK;
}

void GameScene::Update()
{
    //cout << GLOBAL_POS << endl;
    ammoManger.Update();
    itemManager.Update();
    monsterManager.Update();
    mushroom.Update();
    mario->Update();

}

void GameScene::Render(HDC hdc)
{   
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            if (map[i][j].type == BlockType::Background)
            {
                mapSpriteImg->Render(hdc, map[i][j].rc.left + TILE_SIZE / 2 - GLOBAL_POS
                    , (float)map[i][j].rc.top + TILE_SIZE / 2
                    , map[i][j].frameX, map[i][j].frameY);
            }
        }
    }
    itemManager.Render(hdc);
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            if (map[i][j].type != BlockType::Background)
            {
                mapSpriteImg->Render(hdc, map[i][j].rc.left + TILE_SIZE / 2 - GLOBAL_POS
                    , (float)map[i][j].rc.top + TILE_SIZE / 2
                    , map[i][j].frameX, map[i][j].frameY);
            }
        }
    }
    ammoManger.Render(hdc);
    monsterManager.Render(hdc);
    mario->Render(hdc);
    mushroom.Render(hdc);  

}

void GameScene::Release()
{
    //delete[] GameDataContainer::GetSingleton()->map;
    //GameDataContainer::GetSingleton()->Release();
    //GameDataContainer::GetSingleton()->ReleaseSingleton();
    itemManager.Release();
    ammoManger.Release();
    monsterManager.Release();
    SAFE_RELEASE(mario);
}

void GameScene::Load(int loadIndex)
{
    string loadFileName = "Save/saveMapData_" + to_string(loadIndex);
    loadFileName += ".map";

    HANDLE hFile = CreateFile(loadFileName.c_str(),
        GENERIC_READ,           // 읽기, 쓰기
        0, NULL,                // 공유, 보안 모드
        OPEN_EXISTING,          // 파일 만들거나 읽을 때 옵션
        FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등등)
        NULL);

    // 읽기
    DWORD readByte;
    if (ReadFile(hFile, map, sizeof(TILE) * MAP_WIDTH * MAP_HEIGHT,
        &readByte, NULL) == false)
    {
        MessageBox(g_hWnd, "맵 데이터 로드에 실패했습니다.", "에러", MB_OK);
    }

    CloseHandle(hFile);
}
