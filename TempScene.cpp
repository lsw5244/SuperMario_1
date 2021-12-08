#include "TempScene.h"
#include "CommonFunction.h"
#include "Image.h"
#include "Input.h"
#include "GameDataContainer.h"

HRESULT TempScene::Init()
{
    SetWindowSize(300, 20, GAME_SCENE_WIN_SIZE_X, GAME_SCENE_WIN_SIZE_Y);

    mapSpriteImg = ImageManager::GetSingleton()->FindImage("Image/mario_overwordTile.bmp");
    Load();
    GameDataContainer::GetSingleton()->map = map;

    mario.SetPos({ WIN_SIZE_X / 2, WIN_SIZE_Y / 2 });
    mushroom.SetPos({ WIN_SIZE_X / 2, WIN_SIZE_Y / 2 });
    //GameDataContainer::GetSingleton()->SetMap(map);
    return S_OK;
}

void TempScene::Update()
{
    mario.Update();
    mushroom.Update();

    //if (Input::GetButton(VK_RIGHT))
    //{
    //    for (int i = 0; i < MAP_HEIGHT; i++)
    //    {
    //        for (int j = 0; j < MAP_WIDTH; j++)
    //        {
    //            map[i][j].rc.left -= 10;
    //        }
    //    }
    //}

    if (Input::GetButtonDown(VK_SPACE))
    {
        cout << &map << endl;
        cout << GameDataContainer::GetSingleton()->map << endl;
    }
}

void TempScene::Render(HDC hdc)
{   
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            //mapSpriteImg->Render(hdc, GameDataContainer::GetSingleton()->map[i][j].rc.left,                 
            //    GameDataContainer::GetSingleton()->map[i][j].rc.top + TILE_SIZE / 2

            //    , GameDataContainer::GetSingleton()->map[i][j].frameX,
            //    GameDataContainer::GetSingleton()->map[i][j].frameY);

            mapSpriteImg->Render(hdc, map[i][j].rc.left, map[i][j].rc.top + TILE_SIZE / 2
            , map[i][j].frameX, map[i][j].frameY);
            
        }
    }

    mario.Render(hdc);
    mushroom.Render(hdc);
}

void TempScene::Release()
{
    //delete[] GameDataContainer::GetSingleton()->map;
    GameDataContainer::GetSingleton()->Release();
    GameDataContainer::GetSingleton()->ReleaseSingleton();
}

void TempScene::Load(int loadIndex)
{
    string loadFileName = "Save/saveMapData_" + to_string(loadIndex);
    loadFileName += ".map";

    HANDLE hFile = CreateFile(loadFileName.c_str(),
        GENERIC_READ,           // �б�, ����
        0, NULL,                // ����, ���� ���
        OPEN_EXISTING,          // ���� ����ų� ���� �� �ɼ�
        FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ���)
        NULL);

    // �б�
    DWORD readByte;
    if (ReadFile(hFile, map, sizeof(TILE) * MAP_WIDTH * MAP_HEIGHT,
        &readByte, NULL) == false)
    {
        MessageBox(g_hWnd, "�� ������ �ε忡 �����߽��ϴ�.", "����", MB_OK);
    }

    CloseHandle(hFile);
}
