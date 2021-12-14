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
	Brick, CanDestroyBrick, ItemBlock, CoinBlock, StarBlock, HiddenCoinBlcok, HiddenStarBlock,// ���� �� �ִ� ��
	Coin,																																// ������ ���� ������ ��
	Background, FlagEnd,																										// ����, �� �� ��� ��
	Flag, FlagPole, FlagTop,																									//���(������ ���� Ŭ����)
	LateRenderBlock																												// �÷��̾� ���� �� �����Ǵ� ��
};
