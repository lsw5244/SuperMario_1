// CommonFunction.h

#pragma once
#include <Windows.h>
#include <math.h>
#include "GlobalVariableCollection.h"

inline float GetDistance(const POINTFLOAT& pos1, const POINTFLOAT& pos2)
{
	return sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x)
		+ (pos1.y - pos2.y) * (pos1.y - pos2.y));
}

inline void SetWindowSize(int startX, int startY, int sizeX, int sizeY)
{
	// 원하는 윈도우 작업영역 설정
	RECT rc;
	rc.left = 0; rc.top = 0;
	rc.right = sizeX;	rc.bottom = sizeY;

	// 스타일이 포함된 실제 윈도우 크기 계산
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// 계산된 값으로 윈도우를 이동시키면서 크기도 함께 변환
	MoveWindow(g_hWnd, startX, startY,
		rc.right - rc.left, rc.bottom - rc.top, true);
}

inline int GetPosCount(int pos, int isSize, bool isPosX) {
	int Count = 0;

	if (isPosX) {
		Count = ((pos - 16) / 8) % 26;
		Count += isSize;
	} else {
		Count = ((pos - 8) / 8) % 26;
		Count += isSize;
	}
	if (Count < 0) Count = 0;
	if (Count > 26) Count = 26;
	return Count;
}