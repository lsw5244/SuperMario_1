#include "KeyManager.h"

void KeyManager::Init()
{
	for (int i = 0; i < KEY_MAX_COUNT; i++)
	{
		keyUp[i] = true;
		keyDown[i] = false;

		//keyUp.set(i, true);
		//keyDown.set(i, false);

		//keyUp.operator<<
	}
}

void KeyManager::Release()
{
}

bool KeyManager::IsOnceKeyDown(int key)
{
	// �Լ� ȣ�� ������ ����Ű(VK_...)�� � �������� Ȯ���� �����ϴ�.
	/*
		1. 0x0000 ( 0000 0000 0000 0000 )
		-> ���� �����ӿ� �������� ���� ȣ��������� �������� �ʴ�.
		2. 0x0001 ( 0000 0000 0000 0001 )
		-> ���� �����ӿ� �������� �ְ� ȣ��������� �������� �ʴ�.
		3. 0x8000 ( 1000 0000 0000 0000 )
		-> ���� �����ӿ� �������� ���� ȣ��������� �����ִ�.
		4. 0x8001 ( 1000 0000 0000 0001 )
		-> ���� �����ӿ� �������� �ְ� ȣ��������� �����ִ�.
	*/
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (keyDown[key] == false)
		{
			keyDown[key] = true;
			return true;
		}
	}
	else
	{
		keyDown[key] = false;
	}
	return false;
}

bool KeyManager::IsOnceKeyUp(int key)
{
	// �ǽ�1. �� �Լ��� �ϼ��غ���.
	if (GetAsyncKeyState(key) & 0x8000)
	{
		keyUp[key] = false;
	}
	else
	{
		if (keyUp[key] == false)
		{
			keyUp[key] = true;
			return true;
		}
	}

	return false;
}

bool KeyManager::IsStayKeyDown(int key)
{
//	bool b = 0x8000 & 0x8001;

	static time_t currTime;
	// �ǽ�2. �굵 �غ���.
	if (GetAsyncKeyState(key) & 0x8001)
	{
		//cout << "1. true : " << time(&currTime) << endl;
		return true;
	}
	//else
	//{
	//	cout << "2. false : " << time(&currTime) << endl;
	//}

	//if (GetAsyncKeyState(key) & 0x0001)
	//{
	//	cout << "3. true : " << time(&currTime) << endl;
	//	return true;
	//}
	//else
	//{
	//	cout << "4. false : " << time(&currTime) << endl;
	//}
	//cout << endl << endl;

	return false;
}
