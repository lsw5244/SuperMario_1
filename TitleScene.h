#pragma once
#include "GameEntity.h"
class TitleScene : public GameEntity
{
private:

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~TitleScene() = default;
};

