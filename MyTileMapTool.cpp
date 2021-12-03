#include "MyTileMapTool.h"
#include "CommonFunction.h"
#include "Image.h"

#define SPRITE_START_Y 500

HRESULT MyTileMapTool::Init()
{
    //SetWindowSize(20, 20, WinX, WinY);

    if (mapSpriteImg == nullptr)
    {
        cout << "�̹��� ��������Ʈ ����" << endl;
        return E_FAIL;
    }
    // ���� �׸� ���� �ʱ�ȭ
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            SetRect(&map[i][j].rc,
                j * TILE_SIZE,                          // left
                i * TILE_SIZE,                          // top
                j * TILE_SIZE + TILE_SIZE,        // right
                i * TILE_SIZE + TILE_SIZE);       // bottom

            if (i < MAP_HEIGHT - 2)
            {
                map[i][j].frameX = 4;
                map[i][j].frameY = 0;
                map[i][j].type = BlockType::BackGround;
            }
            else
            {
                map[i][j].frameX = 0;
                map[i][j].frameY = 0;
                map[i][j].type = BlockType::BackGround;
            }
        }

    }

    // Ÿ�ϸ� �̹��� ���� �ʱ�ȭ
    for (int i = 0; i < TILE_SPRITE_HEIGHT; i++)
    {
        for (int j = 0; j < TILE_SPRITE_WIDTH; j++)
        {
            SetRect(&sampleTileInfo[i][j].rc,
                j * TILE_SIZE,                        
                i * TILE_SIZE + SPRITE_START_Y,
                j * TILE_SIZE + TILE_SIZE,
                i * TILE_SIZE + TILE_SIZE + SPRITE_START_Y);

            sampleTileInfo[i][j].frameX = j;
            sampleTileInfo[i][j].frameY = i;
        }
    }
    
    selectTile.frameX = 0;
    selectTile.frameY = 0;
	return S_OK;
}

void MyTileMapTool::Update()
{
    RECT spriteImgArea;
    spriteImgArea.left = WIN_SIZE_X - mapSpriteImg->GetWidth();
    spriteImgArea.right = WIN_SIZE_X;
    spriteImgArea.top = SPRITE_START_Y;
    spriteImgArea.bottom = SPRITE_START_Y + mapSpriteImg->GetHeight();

    if (PtInRect(&(spriteImgArea), g_ptMouse))
    {
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
        {
            int posX = g_ptMouse.x - spriteImgArea.left;  // spriteImgArea�� � ��ǥ�� �ִ��� ���ϱ�
            int selectIdxX = posX / TILE_SIZE;

            int posY = g_ptMouse.y - spriteImgArea.top;
            int selectIdxY = posY / TILE_SIZE;

            selectTile.frameX = selectIdxX;
            selectTile.frameY = selectIdxY;
        }
    }
    RECT mapArea;
    mapArea.left = 0;
    mapArea.right = TILE_SIZE * MAP_WIDTH;
    mapArea.top = 0;
    mapArea.bottom = TILE_SIZE * MAP_HEIGHT;

    if (PtInRect(&(mapArea), g_ptMouse))
    {
        if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
        {
            int posX = g_ptMouse.x;
            int selectIdxX = (posX / TILE_SIZE) + (page * MAP_WIDTH_PER_PAGE);

            int posY = g_ptMouse.y;
            int selectIdxY = posY / TILE_SIZE;

            map[selectIdxY][selectIdxX].frameX = selectTile.frameX;
            map[selectIdxY][selectIdxX].frameY = selectTile.frameY;
        }
    }

    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LEFT))
    {
        --page;
        page = max(page, 0);
        cout << page << endl;
    }
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RIGHT))
    {
        ++page;
        page = min(page, 4);
        cout << page << endl;
    }

    if (KeyManager::GetSingleton()->IsOnceKeyUp('S'))
    {
        Save();
    }

    if (KeyManager::GetSingleton()->IsOnceKeyUp('L'))
    {
        Load();
    }

}

void MyTileMapTool::Render(HDC hdc)
{
    // Ÿ�� �� ���� ����
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH_PER_PAGE; j++)        // �������� ���� ��ܿ;� �� ?
        {
            mapSpriteImg->Render(hdc,
                map[i][j/* + (page * MAP_WIDTH_PER_PAGE)*/].rc.left + TILE_SIZE / 2,
                map[i][j/* + (page * MAP_WIDTH_PER_PAGE)*/].rc.top + TILE_SIZE / 2,
                map[i][j + (page * MAP_WIDTH_PER_PAGE)].frameX,
                map[i][j + (page * MAP_WIDTH_PER_PAGE)].frameY
            );
        }
    }

    //for (int i = 0; i < TILE_SPRITE_HEIGHT; i++)
    //{
    //    for (int j = 0; j < TILE_SPRITE_WIDTH; j++)
    //    {
    //        // l t r b
    //        Rectangle(hdc, sampleTileInfo[i][j].rc.left,
    //            sampleTileInfo[i][j].rc.top,
    //            sampleTileInfo[i][j].rc.right,
    //            sampleTileInfo[i][j].rc.bottom);
    //    }
    //}

    // ��������Ʈ �̹��� ����
    mapSpriteImg->Render(hdc,
        WIN_SIZE_X - mapSpriteImg->GetWidth() + mapSpriteImg->GetWidth() / 2, // �������� x
        mapSpriteImg->GetHeight() / 2 + SPRITE_START_Y);                                 // �������� y

    // ������ Ÿ�� ����
    mapSpriteImg->Render(hdc,
        WIN_SIZE_X/* - TILE_SIZE*/ / 2,
        WIN_SIZE_X - TILE_SIZE,
        selectTile.frameX,
        selectTile.frameY);
}

void MyTileMapTool::Release()
{
}

void MyTileMapTool::Save(int saveIndex)
{
    string saveFileName = "Save/saveMapData_" + to_string(saveIndex);
    saveFileName += ".map";

    HANDLE hFile = CreateFile(saveFileName.c_str(),
        GENERIC_WRITE,          // �б�, ����
        0, NULL,                // ����, ���� ���
        CREATE_ALWAYS,          // ���� ����ų� ���� �� �ɼ�
        FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ���)
        NULL);

    // ����
    DWORD byteSize = sizeof(TILE) * MAP_WIDTH * MAP_HEIGHT;

    DWORD writtenByte;
    if (WriteFile(hFile,    // ���� �ڵ�
        map,       // �޸� �����ּ�
        sizeof(TILE) * MAP_WIDTH * MAP_HEIGHT,  // �޸� ũ��
        &writtenByte,   // ���� ������ ���� �뷮
        NULL) == false)          // ???
    {
        MessageBox(g_hWnd, "�� ������ ���忡 �����߽��ϴ�.", "����", MB_OK);
    }

    CloseHandle(hFile);

    //(parsing)  .ini, .json, html
}

void MyTileMapTool::Load(int loadIndex)
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
