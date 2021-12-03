#include "UIManager.h"
#include "PlayerStatus.h"
#include "EnemyStatus.h"
#include "Config.h"

HRESULT UIManager::Init()
{
    playerStatus = new PlayerStatus;
    playerStatus->Init();
    enemyStatus = new EnemyStatus;
    enemyStatus->Init();
    return S_OK;
}

void UIManager::SetData(PlayerTank* playerTank, StageManager* stageManager)
{
    playerStatus->SetData(playerTank);
    enemyStatus->SetData(stageManager);
}

void UIManager::Update()
{
    playerStatus->Update();
    enemyStatus->Update();
}

void UIManager::Render(HDC hdc)
{
    playerStatus->Render(hdc);
    enemyStatus->Render(hdc);
}

void UIManager::Release()
{
    SAFE_DELETE(playerStatus);
    SAFE_DELETE(enemyStatus);
}
