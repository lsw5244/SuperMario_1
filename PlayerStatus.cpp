#include "PlayerStatus.h"
#include "Image.h"

void PlayerStatus::SetData(PlayerTank* playerTank)
{
	this->playerTank = playerTank;
}

HRESULT PlayerStatus::Init()
{
	player1LifeImage = ImageManager::GetSingleton()->FindImage("Image/Icon/player1Life.bmp");
	lifeNumImage = ImageManager::GetSingleton()->FindImage("Image/Text/Number.bmp");

	return S_OK;
}

void PlayerStatus::Update()
{
	ChangeLifeImage(playerTank->GetLife());
}

void PlayerStatus::Render(HDC hdc)
{
	player1LifeImage->Render(hdc, 240, 136);
	lifeNumImage->Render(hdc, 244, 140, lifeNumImage->GetCurrFrameX(), lifeNumImage->GetCurrFrameY());
}

void PlayerStatus::Release()
{
}

void PlayerStatus::ChangeLifeImage(int life)
{
	lifeNumImage->SetCurrFrameX(life % 5);
	lifeNumImage->SetCurrFrameY(life / 5);
}
