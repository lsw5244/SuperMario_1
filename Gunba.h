#pragma once
#include "GameEntity.h"
#include "HeaderCollection.h"

class Image;
class Gunba : public GameEntity
{
private:
	Image* img = ImageManager::GetSingleton()->FindImage("Image/Monster/Gunba.bmp");

	POINTFLOAT pos = { 0,0 };

	int frameX = 0;
	int frameY = 1;	// 기본적으로 왼쪽을 향함

	float gravity = 0.1f;
	float resistance = 0.02f;
	float moveSpeed = -1.0f;

	bool isDead = false;

	void AutoMove();
	void AnimationFrameChanger();
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	Gunba() = default;
	virtual ~Gunba() = default;

	void SetPos(POINTFLOAT pos)
	{
		this->pos = pos;
	}
	POINTFLOAT GetPos()
	{
		return pos;
	}
};

