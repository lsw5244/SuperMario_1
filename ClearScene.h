#pragma once
#include "GameEntity.h"

class Image;
class ClearScene : public GameEntity
{
private:
	Image* background = nullptr;

	float elapsedTime = 0.0f;
	float changeSceneDelay = 2.0f;

public:
	virtual HRESULT Init()		 override;
	virtual void Update()		 override;
	virtual void Render(HDC hdc) override;
	virtual void Release()		 override;
	virtual ~ClearScene() = default;

};

