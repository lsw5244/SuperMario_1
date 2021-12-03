#include "MyTileMapTool.h"
#include "CommonFunction.h"
#include "Image.h"

#define SPRITE_START_Y 500

HRESULT MyTileMapTool::Init()
{
    //SetWindowSize(20, 20, WinX, WinY);

    if (mapSpriteImg == nullptr)
    {
        cout << "이미지 스프라이트 없음" << endl;
        return E_FAIL;
    }
    // 맵을 그릴 영역 초기화
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

    // 타일맵 이미지 영역 초기화
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
            int posX = g_ptMouse.x - spriteImgArea.left;  // spriteImgArea의 어떤 좌표에 있는지 구하기
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
    // 타일 맵 찍을 영역
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH_PER_PAGE; j++)        // 페이지에 따라 당겨와야 함 ?
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

    // 스프라이트 이미지 영역
    mapSpriteImg->Render(hdc,
        WIN_SIZE_X - mapSpriteImg->GetWidth() + mapSpriteImg->GetWidth() / 2, // 시작지점 x
        mapSpriteImg->GetHeight() / 2 + SPRITE_START_Y);                                 // 시작지점 y

    // 선택한 타일 보기
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
        GENERIC_WRITE,          // 읽기, 쓰기
        0, NULL,                // 공유, 보안 모드
        CREATE_ALWAYS,          // 파일 만들거나 읽을 때 옵션
        FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등등)
        NULL);

    // 쓰기
    DWORD byteSize = sizeof(TILE) * MAP_WIDTH * MAP_HEIGHT;

    DWORD writtenByte;
    if (WriteFile(hFile,    // 파일 핸들
        map,       // 메모리 시작주소
        sizeof(TILE) * MAP_WIDTH * MAP_HEIGHT,  // 메모리 크기
        &writtenByte,   // 실제 쓰여진 파일 용량
        NULL) == false)          // ???
    {
        MessageBox(g_hWnd, "맵 데이터 저장에 실패했습니다.", "에러", MB_OK);
    }

    CloseHandle(hFile);

    //(parsing)  .ini, .json, html
}

void MyTileMapTool::Load(int loadIndex)
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
