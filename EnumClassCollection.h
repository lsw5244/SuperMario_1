#pragma once

enum class MoveDirection
{
	Left, Right, End
};

enum class BlockType
{
	Brick, CanDestroyBrick, ItemBlock, CoinBlock, StarBlock, HiddenCoinBlcok, HiddenStarBlock,// ���� �� �ִ� ��
	Coin,																																// ������ ���� ������ ��
	Background, FlagEnd,																										// ����, �� �� ��� ��
	Flag, FlagPole, FlagTop,																									//���(������ ���� Ŭ����)
	LateRenderBlock																												// �÷��̾� ���� �� �����Ǵ� ��
};
