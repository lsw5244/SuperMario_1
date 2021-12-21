#pragma once
#include "GameEntity.h"

class Image;
class TitleScene : public GameEntity
{
private:
	Image* backGround = nullptr;
	Image* selectImage = nullptr;

	POINT selectImagePos = {};
	const int selectImagePosX = 76;
	const int selectImageTopPosY = 148;
	const int selectImageBottomPosY = 164;


public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~TitleScene() = default;
};

