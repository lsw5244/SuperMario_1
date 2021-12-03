#include "TotalScene.h"
#include "CommonFunction.h"
#include "Image.h"
#include "ScoreManager.h"
#include "TimerManager.h"
#include "SceneManager.h"
#include "GameDataManager.h"

HRESULT TotalScene::Init()
{
	SetWindowSize(300, 20, WIN_SIZE_X * 4, WIN_SIZE_Y * 4);
	windowX = WIN_SIZE_X, windowY = WIN_SIZE_Y;

	hiScore = ImageManager::GetSingleton()->FindImage("Image/Text/HISocre.bmp");

	for (int i = 0; i < 10; i++)
	{
		wNumberImage[i] = ImageManager::GetSingleton()->FindImage("Image/Text/Number_w.bmp");
	}
	player1 = ImageManager::GetSingleton()->FindImage("Image/Text/Player1.bmp");
	points = ImageManager::GetSingleton()->FindImage("Image/Text/PTS.bmp");
	scoreNumber = ImageManager::GetSingleton()->FindImage("Image/Text/ScoreNumber.bmp");
	wStage = ImageManager::GetSingleton()->FindImage("Image/Text/Stage_w.bmp");
	enemyTankImage = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	arrow = ImageManager::GetSingleton()->FindImage("Image/Icon/Arrow.bmp");
	totalScoreWord = ImageManager::GetSingleton()->FindImage("Image/Text/TotalScore.bmp");
	gameOver = ImageManager::GetSingleton()->FindImage("Image/Title/ScoreGameOver.bmp");
	gameClear = ImageManager::GetSingleton()->FindImage("Image/Title/GameClear.bmp");

	gameOverPos = WIN_SIZE_Y + (gameOver->GetHeight() / 2);
	gameClearPos = WIN_SIZE_Y + (gameClear->GetHeight() / 2);
	nextSceneTime = 0;
	sceneChangeTime = 3;
	stageNum = GameDataManager::GetSingleton()->GetIsStage();

	normal = 0;
	fastMove = 0;
	fastShoot = 0;
	bigTank = 0;

	normalScoreRender = false;
	fastMoveScoreRender = false;
	fastShootScoreRender = false;
	bigTankScoreRender = false;
	totalDestroyScoreRender = false;

	textAnimateEnd = false;
	return S_OK;
}

void TotalScene::Update()
{
	totalNormal = ScoreManager::GetSingleton()->GetTotalNormal();
	totalFastMove = ScoreManager::GetSingleton()->GetTotalFastMove();
	totalFastShoot = ScoreManager::GetSingleton()->GetTotalFastShoot();
	totalBigTank = ScoreManager::GetSingleton()->GetTotalBigTank();
	totalDestroy = ScoreManager::GetSingleton()->GetTotalDestroy();
	totalScore = ScoreManager::GetSingleton()->GetTotalScore();
	prevTotalScore = ScoreManager::GetSingleton()->GetPrevTotalScore();

	scoreTextTic1 += TimerManager::GetSingleton()->GetDeltaTime();
	scoreTextTic2 += TimerManager::GetSingleton()->GetDeltaTime();

	if (scoreTextTic2 > 0.5)
	{
		if((normal == totalNormal) && normalScoreRender)
		{
			if((fastMove == totalFastMove) && fastMoveScoreRender)
			{
				if ((fastShoot == totalFastShoot) && fastShootScoreRender)
				{
					if ((bigTank == totalBigTank) && bigTankScoreRender) totalDestroyScoreRender = true;
					bigTankScoreRender = true;
				}
				fastShootScoreRender = true;

			}
			fastMoveScoreRender = true;
		}
		normalScoreRender = true;
		scoreTextTic2 = 0;
	}
	if ((scoreTextTic1 > 0.15) && (normal < totalNormal) && normalScoreRender)
	{
		normal++;
		scoreTextTic1 = 0;
	}
	if ((scoreTextTic1 > 0.15) && (fastMove < totalFastMove) && fastMoveScoreRender)
	{
		fastMove++;
		scoreTextTic1 = 0;
	}
	if ((scoreTextTic1 > 0.15) && (fastShoot < totalFastShoot) && fastShootScoreRender)
	{
		fastShoot++;
		scoreTextTic1 = 0;
	}
	if ((scoreTextTic1 > 0.15) && (bigTank < totalBigTank) && bigTankScoreRender)
	{
		bigTank++;
		scoreTextTic1 = 0;
	}
	if (bigTank == totalBigTank && totalDestroyScoreRender)
	{
		textAnimateEnd = true;
	}

	if (textAnimateEnd == true)
	{
		nextSceneTime += TimerManager::GetSingleton()->GetDeltaTime();
		if (GameDataManager::GetSingleton()->GetPlayerIsDead()) {	// 플레이어 사망시
			if (nextSceneTime > sceneChangeTime) {
				if (gameOverPos > WIN_SIZE_Y / 2) {
					gameOverPos -= 80 * TimerManager::GetSingleton()->GetDeltaTime();
				}
			}
			if (nextSceneTime > sceneChangeTime + 3) {
				if (GameDataManager::GetSingleton()->GetPlayerIsDead()) {
					GameDataManager::GetSingleton()->SetStage(1);
					SceneManager::GetSingleton()->ChangeScene("TitleScene");
				}
			}
		}
		else if (!GameDataManager::GetSingleton()->GetPlayerIsDead()) {
			if (stageNum != 11) {
				if (nextSceneTime > sceneChangeTime) {		// 스테이지 클리어후 다음스테이지 전환
					if (!GameDataManager::GetSingleton()->GetPlayerIsDead()) {
						SceneManager::GetSingleton()->ChangeScene("BattleScene");
					}
				}
			}
			else {	// 10스테이지 클리어 했을 경우
				if (nextSceneTime > sceneChangeTime) {
					if (gameClearPos > WIN_SIZE_Y / 2) {
						gameClearPos -= 80 * TimerManager::GetSingleton()->GetDeltaTime();
					}
				}
				if (nextSceneTime > sceneChangeTime + 4) {	
					GameDataManager::GetSingleton()->SetStage(1);
					SceneManager::GetSingleton()->ChangeScene("TitleScene");
				}
			}
		}

	}
}

void TotalScene::Render(HDC hdc)
{
	if (nextSceneTime > sceneChangeTime) {
		gameOver->Render(hdc, WIN_SIZE_X / 2, gameOverPos);
		gameClear->Render(hdc, WIN_SIZE_X / 2, gameClearPos);
		return;
	}

	hiScore->Render(hdc, WIN_SIZE_X / 2, 20);	//고정
	wStage->Render(hdc, WIN_SIZE_X / 2 - 13, 36);	//고정
	for (int i = 0; i < 10; i++)
	{
		ScoreRender(hdc, i);
	}

	player1->Render(hdc, WIN_SIZE_X / 2 - 74, 52);
	totalScoreWord->Render(hdc, WIN_SIZE_X / 2 - 25, 177);


	for (int i = 0; i < 4; i++)
	{
		points->Render(hdc, WIN_SIZE_X / 2 - 54, 92 + (24 * i));
		enemyTankImage->Render(hdc, WIN_SIZE_X / 2, 92 + (24 * i), 0, i);
		arrow->Render(hdc, WIN_SIZE_X / 2 - 13, 92 + (24 * i));
	}
	
	if (prevTotalScore > 9)
	{
		if (999999 > prevTotalScore && prevTotalScore > 99999)
		{
			scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 90, 68, (prevTotalScore / 100000) % 5, ((prevTotalScore / 100000) / 5));
			scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 81, 68, ((prevTotalScore % 100000) / 10000) % 5, (((prevTotalScore / 100000) / 10000) / 5));
			scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 72, 68, ((prevTotalScore % 10000) / 1000) % 5, ((prevTotalScore % 10000) / 1000) / 5);
			scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 63, 68, ((prevTotalScore % 1000) / 100) % 5, ((prevTotalScore % 1000) / 100) / 5);
		}

		else if (99999 > prevTotalScore && prevTotalScore > 9999)
		{
			scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 81, 68, (prevTotalScore / 10000) % 5, ((prevTotalScore / 10000) / 5));
			scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 72, 68, ((prevTotalScore % 10000) / 1000) % 5, ((prevTotalScore % 10000) / 1000) / 5);
			scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 63, 68, ((prevTotalScore % 1000) / 100) % 5, ((prevTotalScore % 1000) / 100) / 5);
		}
		else if (9999 > prevTotalScore && prevTotalScore > 999)
		{
			scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 72, 68, (prevTotalScore / 1000) % 5, (prevTotalScore / 1000) / 5);
			scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 63, 68, ((prevTotalScore % 1000) / 100) % 5, ((prevTotalScore % 1000) / 100) / 5);
		}
		else if (999 > prevTotalScore && prevTotalScore > 99)
		{
			scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 63, 68, (prevTotalScore / 100) % 5, ((prevTotalScore / 100) / 5));
		}
		scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 54, 68, 0, 0);
	}
	scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 45, 68, 0, 0);

}

void TotalScene::Release()
{
}

void TotalScene::ScoreRender(HDC hdc, int i)
{
	switch (i)
	{
	case 0:
		if (((stageNum-1) > 9))
		{
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 + 23, 36, ((stageNum - 1) / 10) % 5, (((stageNum - 1) / 10) / 5));
		}
		wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 + 31, 36, ((stageNum - 1) % 10) % 5, (((stageNum - 1) % 10) / 5));
		break;
	case 1:
		if (normalScoreRender)
		{
			if ((normal > 9))
			{
				wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 29, 92, (normal / 10) % 5, ((normal / 10) / 5));
			}
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 21, 92, (normal % 10) % 5, ((normal % 10) / 5));
		}
		break;
	case 2:
		if (fastMoveScoreRender)
		{
			if (fastMove > 9)
			{
				wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 29, 116, (fastMove / 10) % 5, ((fastMove / 10) / 5));
			}
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 21, 116, (fastMove % 10) % 5, ((fastMove % 10) / 5));
		}
		break;
	case 3:
		if (fastShootScoreRender)
		{
			if (fastShoot > 9)
			{
				wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 29, 140, (fastShoot / 10) % 5, ((fastShoot / 10) / 5));
			}
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 21, 140, (fastShoot % 10) % 5, ((fastShoot % 10) / 5));
		}
		break;
	case 4:
		if (bigTankScoreRender)
		{
			if (bigTank > 9)
			{
				wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 29, 164, (bigTank / 10) % 5, ((bigTank / 10) / 5));
			}
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 21, 164, (bigTank % 10) % 5, ((bigTank % 10) / 5));
		}
		break;
	case 5:
		if (normalScoreRender)
		{
			if (normal > 9)
			{
				wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 103, 92, (normal / 10) % 5, ((normal / 10) / 5));
			}
			if (normal > 0)
			{
				wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 94, 92, (normal % 10) % 5, ((normal % 10) / 5));
				wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 85, 92, 0, 0);
			}
				wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 76, 92, 0, 0);
		}
		break;
	case 6:
		if (fastMoveScoreRender)
		{
			if (fastMove * 2 > 9)
			{
				wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 103, 116, (fastMove * 2 / 10) % 5, ((fastMove * 2 / 10) / 5));
			}
			if (fastMove > 0)
			{
				wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 94, 116, (fastMove * 2 % 10) % 5, ((fastMove * 2 % 10) / 5));
				wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 85, 116, 0, 0);
			}
				wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 76, 116, 0, 0);
		}
		break;
	case 7:
		if (fastShootScoreRender)
		{
			if (fastShoot * 3 > 9)
			{
				wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 103, 140, (fastShoot * 3 / 10) % 5, ((fastShoot * 3 / 10) / 5));
			}
			if (fastShoot > 0)
			{
				wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 94, 140, (fastShoot * 3 % 10) % 5, ((fastShoot * 3 % 10) / 5));
				wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 85, 140, 0, 0);
			}
				wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 76, 140, 0, 0);
		}
		break;
	case 8:
		if (bigTankScoreRender)
		{
			if (bigTank * 4 > 9)
			{
				wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 103, 164, (bigTank * 4 / 10) % 5, ((bigTank * 4 / 10) / 5));
			}
			if (bigTank > 0)
			{
				wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 94, 164, (bigTank * 4 % 10) % 5, ((bigTank * 4 % 10) / 5));
				wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 85, 164, 0, 0);
			}
				wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 76, 164, 0, 0);
		}
		break;
	case 9:
		if (totalDestroyScoreRender)
		{
			if (totalDestroy > 9)
			{
				wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 29, 178, (totalDestroy / 10) % 5, ((totalDestroy / 10) / 5));
			}
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 21, 178, (totalDestroy % 10) % 5, ((totalDestroy % 10) / 5));
		}
		break;
	}
}
