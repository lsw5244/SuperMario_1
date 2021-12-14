#pragma once

enum MoveDirection
{
	Left, Right
};
enum PlayerAnimation
{
	Idle, Run1, Run2, Run3, ChangeDirection, Sit, Jump, Die, Grow1, Grow2, Grow3, Attack, Flag1, Flag2
};

enum class BlockType
{
	Brick, CanDestroyBrick, ItemBlock, CoinBlock, StarBlock, HiddenCoinBlcok, HiddenStarBlock,// 밟을 수 있는 블럭
	Coin,																																// 닿으면 점수 오르는 블럭
	Background, FlagEnd,																										// 구름, 산 등 배경 블럭
	Flag, FlagPole, FlagTop,																									//깃발(닿으면 게임 클리어)
	LateRenderBlock																												// 플레이어 랜더 후 랜더되는 블럭
};
