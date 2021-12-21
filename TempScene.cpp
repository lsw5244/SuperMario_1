#include "TempScene.h"
#include "CommonFunction.h"
#include "Image.h"
#include "Input.h"
#include "GameDataContainer.h"
#include "AmmoManager.h"

HRESULT TempScene::Init()
{
    SetWindowSize(300, 20, GAME_SCENE_WIN_SIZE_X, GAME_SCENE_WIN_SIZE_Y);

    GameDataContainer::GetInstance()->SetGlobalPos(0);

    mapSpriteImg = ImageManager::GetInstance()->FindImage("Image/mario_overwordTile.bmp");
    Load();
    GameDataContainer::GetInstance()->map = map;
    
    mario.SetPos({ WIN_SIZE_X / 3, WIN_SIZE_Y / 2 });
    GameDataContainer::GetInstance()->SetPlayer(&mario);

    mushroom.Init();
    mushroom.SetPos({ WIN_SIZE_X / 2, WIN_SIZE_Y / 2 });

    ammoManger.Init();
    GameDataContainer::GetInstance()->SetAmmoManager(&ammoManger);

    itemManager.Init();
    GameDataContainer::GetInstance()->SetItemManager(&itemManager);

    return S_OK;
}

void TempScene::Update()
{
    mario.Update();
    //mushroom.Update();
    ammoManger.Update();
    itemManager.Update();
    //if (Input::GetButton(VK_RIGHT) &&
    //    GameDataContainer::GetInstance()->GetPlayer()->GetPos().x > WIN_SIZE_X / 2)
    //{
    //    GameDataContainer::GetInstance()->SetGlobalPos(GLOBAL_POS + GameDataContainer::GetInstance()->GetPlayer()->GetCurrSpeed());
    //}
}

void TempScene::Render(HDC hdc)
{   
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            if (map[i][j].type == BlockType::Background)
            {
                mapSpriteImg->Render(hdc, map[i][j].rc.left + TILE_SIZE / 2 - GLOBAL_POS
                    , map[i][j].rc.top + TILE_SIZE / 2
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
                    , map[i][j].rc.top + TILE_SIZE / 2
                    , map[i][j].frameX, map[i][j].frameY);
            }
        }
    }
    mario.Render(hdc);
    mushroom.Render(hdc);  
    ammoManger.Render(hdc);
}

void TempScene::Release()
{
    //delete[] GameDataContainer::GetSingleton()->map;
    //GameDataContainer::GetSingleton()->Release();
    //GameDataContainer::GetSingleton()->ReleaseSingleton();
    itemManager.Release();
    ammoManger.Release();
}

void TempScene::Load(int loadIndex)
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
