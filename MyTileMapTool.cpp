#include "MyTileMapTool.h"
#include "CommonFunction.h"
#include "Image.h"

#define SPRITE_START_Y 500

void MyTileMapTool::InputTileInfo(int r, int c)
{
    // Brick 0.0   0.2  2.0~5  3.0~5  4.0~1    6~10. 10

    // CanDestroyBrick  0.1

    // ItemBlock  6.7

    // CoinBlock  7.7

    // StarBlock  10. 7

    // HiddenCoinBlcok 8. 9

    // HiddenStarBlock 9. 9


    // Coin  0, 3


    // Flag 11, 1

    // FlagPole 12, 1

    // FlagTop  10, 1

    // FlagEnd 11, 0


    // LateRenderBlock   3, 9   4, 9,  3, 10    4, 10


    // 그외 Background

}

void MyTileMapTool::SelectTileInfoSet(int frameX, int frameY)
{
    // Brick 0. 0,2   2.0~5  3.0~5  4.0~1    6~10. 10
    if (
        (frameX == 0 || frameX == 2)
            && frameY == 0 ||

        (frameX == 0 || frameX == 1 || frameX == 2 || frameX == 3 || frameX == 4 || frameX == 5) 
            && (frameY == 2 || frameY == 3) ||

        (frameX == 0 || frameX == 1) 
            && frameY == 4 ||

        frameX == 10 
            && (frameY == 6 || frameY == 7 || frameY == 8 || frameY == 9 || frameY == 10)
        )
    {
        TileInfoSetting(selectTile, BlockType::Brick, frameX, frameY, 0, 0, 0, true);
    }

    // CanDestroyBrick  0.1
    else if (frameX == 1 && frameY == 0)
    {
        TileInfoSetting(selectTile, BlockType::CanDestroyBrick, frameX, frameY, 0, 0, 0, true);
    }

    // ItemBlock  6.7
    else if (frameX == 7 && frameY == 6)
    {
        TileInfoSetting(selectTile, BlockType::ItemBlock, frameX, frameY, 0, 2, 1, true);
    }

    // CoinBlock  7.7
    else if (frameX == 7 && frameY == 7)
    {
        TileInfoSetting(selectTile, BlockType::CoinBlock, frameX, frameY, 0, 2, 1, true);
    }

    // StarBlock  10. 7
    else if (frameX == 7 && frameY == 10)
    {
        TileInfoSetting(selectTile, BlockType::StarBlock, frameX, frameY, 0, 2, 1, true);
    }
    // HiddenCoinBlcok 8. 9
    else if (frameX == 9 && frameY == 8)
    {
        TileInfoSetting(selectTile, BlockType::HiddenCoinBlcok, frameX, frameY, 0, 0, 3, true);
    }
    // HiddenStarBlock 9. 9
    else if (frameX == 9 && frameY == 9)
    {
        TileInfoSetting(selectTile, BlockType::HiddenStarBlock, frameX, frameY, 0, 0, 1, true);
    }


    // Coin  0, 3
    else if (frameX == 3 && frameY == 0)
    {
        TileInfoSetting(selectTile, BlockType::Coin, frameX, frameY, 0, 0, 0, false);
    }

    // Flag 11, 1
    else if (frameX == 1 && frameY == 11)
    {
        TileInfoSetting(selectTile, BlockType::Flag, frameX, frameY, 0, 0, 0, false);
    }

    // FlagPole 12, 1
    else if (frameX == 1 && frameY == 12)
    {
        TileInfoSetting(selectTile, BlockType::FlagPole, frameX, frameY, 0, 0, 0, false);
    }

    // FlagTop  10, 1
    else if (frameX == 1 && frameY == 10)
    {
        TileInfoSetting(selectTile, BlockType::FlagTop, frameX, frameY, 0, 0, 0, false);
    }

    // FlagEnd 11, 0
    else if (frameX == 0 && frameY == 11)
    {
        TileInfoSetting(selectTile, BlockType::FlagEnd, frameX, frameY, 0, 0, 0, false);
    }

    // LateRenderBlock   3, 9   4, 9,  3, 10    4, 10
    else if (
        frameX == 9
        && (frameY == 3 || frameY == 4) ||

        frameX == 10
        && (frameY == 3 || frameY == 4)
        )
    {
        TileInfoSetting(selectTile, BlockType::LateRenderBlock, frameX, frameY, 0, 0, 0, false);
    }

    // 그외 Background
    else
    {
        TileInfoSetting(selectTile, BlockType::Background, frameX, frameY, 0, 0, 0, false);
    }
}

void MyTileMapTool::TileInfoSetting(TILE& tile, BlockType type, int frameX, int frameY, int animationFrameX, int maxAnimationFrameX, int itemCount, bool isCollider)
{
    tile.frameX             = frameX;
    tile.frameY             = frameY;
    tile.type               = type;
    tile.animationFrameX    = animationFrameX;
    tile.maxAnimationFrameX = maxAnimationFrameX;
    tile.itemCount          = itemCount;
    tile.isCollider         = isCollider;
}

HRESULT MyTileMapTool::Init()
{
    mapSpriteImg = ImageManager::GetInstance()->FindImage("Image/mario_overwordTile.bmp");

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
                // 기본 배경
                TileInfoSetting(map[i][j], BlockType::Background, 4, 0, 0, 0, 0, false);
            }
            else
            {
                // 기본 바닥
                TileInfoSetting(map[i][j], BlockType::Brick, 0, 0, 0, 0, 0, true);
            }
        }
    }

    // 타일맵 이미지 영역 초기화
    for (int i = 0; i < TILE_SPRITE_HEIGHT; i++)
    {
        for (int j = 0; j < TILE_SPRITE_WIDTH; j++)
        {
            SetRect(&sampleTileInfo[i][j].rc,
                j * TILE_SIZE  + (WIN_SIZE_X - mapSpriteImg->GetWidth()),
                i * TILE_SIZE + SPRITE_START_Y,
                j * TILE_SIZE + TILE_SIZE + (WIN_SIZE_X - mapSpriteImg->GetWidth()),
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
        if (KeyManager::GetInstance()->IsOnceKeyDown(VK_LBUTTON))
        {
            int posX = g_ptMouse.x - spriteImgArea.left;  // spriteImgArea의 어떤 좌표에 있는지 구하기
            int selectIdxX = posX / TILE_SIZE;

            int posY = g_ptMouse.y - spriteImgArea.top;
            int selectIdxY = posY / TILE_SIZE;

            /*selectTile.frameX = selectIdxX;
            selectTile.frameY = selectIdxY;*/
            SelectTileInfoSet(selectIdxX, selectIdxY);

            //switch (selectTile.type)
            //{
            //case BlockType::Brick:
            //    cout << "BRICK @@@@" << endl;
            //    break;
            //default:
            //    break;
            //}
            //cout << selectTile.frameX << endl;
            //cout << selectTile.frameY << endl;

            //cout << "-------------------------------\n";
        }
    }
    RECT mapArea;
    mapArea.left = 0;
    mapArea.right = TILE_SIZE * MAP_WIDTH;
    mapArea.top = 0;
    mapArea.bottom = TILE_SIZE * MAP_HEIGHT;

    if (PtInRect(&(mapArea), g_ptMouse))
    {
        if (KeyManager::GetInstance()->IsStayKeyDown(VK_LBUTTON))
        {
            int posX = g_ptMouse.x;
            int selectIdxX = (posX / TILE_SIZE) + (page * MAP_WIDTH_PER_PAGE);

            int posY = g_ptMouse.y;
            int selectIdxY = posY / TILE_SIZE;

            /*map[selectIdxY][selectIdxX].frameX = selectTile.frameX;
            map[selectIdxY][selectIdxX].frameY = selectTile.frameY;*/
            TileInfoSetting(map[selectIdxY][selectIdxX],
                selectTile.type, 
                selectTile.frameX, selectTile.frameY,
                selectTile.animationFrameX, 
                selectTile.maxAnimationFrameX, 
                selectTile.itemCount, selectTile.isCollider);
        }
    }

    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_LEFT))
    {
        --page;
        page = max(page, 0);
        cout << page << endl;
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_RIGHT))
    {
        ++page;
        page = min(page, MAX_PAGE);
        cout << page << endl;
    }

    if (KeyManager::GetInstance()->IsOnceKeyUp('S'))
    {
        Save();
    }

    if (KeyManager::GetInstance()->IsOnceKeyUp('L'))
    {
        Load();
    }

}

void MyTileMapTool::Render(HDC hdc)
{
    // 실제 찍힌 맵을 랜더
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH_PER_PAGE; j++)
        {
            //int b = MAP_WIDTH_PER_PAGE * page + j;
            if (MAP_WIDTH_PER_PAGE * page + j < MAP_WIDTH)
            {
                mapSpriteImg->Render(hdc,
                    map[i][j].rc.left + TILE_SIZE / 2,
                    map[i][j].rc.top + TILE_SIZE / 2,
                    map[i][j + (page * MAP_WIDTH_PER_PAGE)].frameX,
                    map[i][j + (page * MAP_WIDTH_PER_PAGE)].frameY
                );
            }
        }
    }

    for (int i = 0; i < TILE_SPRITE_HEIGHT; i++)
    {
        for (int j = 0; j < TILE_SPRITE_WIDTH; j++)
        {
            Rectangle(hdc, sampleTileInfo[i][j].rc.left
            , sampleTileInfo[i][j].rc.top
            , sampleTileInfo[i][j].rc.right
            , sampleTileInfo[i][j].rc.bottom);
        }
    }

    // 스프라이트 이미지 영역
    mapSpriteImg->Render(hdc,
        WIN_SIZE_X - mapSpriteImg->GetWidth() + mapSpriteImg->GetWidth() / 2, // 시작지점 x
        mapSpriteImg->GetHeight() / 2 + SPRITE_START_Y);                                 // 시작지점 y

    // 선택한 타일 보기
    mapSpriteImg->Render(hdc,
        WIN_SIZE_X / 2,
        WIN_SIZE_Y / 2,
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
