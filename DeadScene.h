#pragma once
#include "GameEntity.h"

class Image;
class DeadScene : public GameEntity
{
private:
	Image* background		 = nullptr;

	float elapsedTime		 = 0.0f;
	float changeSceneDelay	 = 1.5f;

public:
	virtual HRESULT Init()		 override;
	virtual void Update()		 override;
	virtual void Render(HDC hdc) override;
	virtual void Release()		 override;
	virtual ~DeadScene() = default;
};

