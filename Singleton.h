// Singleton.h

// �̱��� ���� : ���α׷����� �ϳ��� �����ϴ� ��ü�� �ʿ��� �� ���Ǵ� ����
// ���� ) Ű �Ŵ��� (�����ϴ� ��ü), �� �Ŵ���, �÷��̾� ������...

#pragma once

//goto

template <typename T>
/*static*/ class Singleton
{
protected:
	static T* instance;		// static ��� ����

	Singleton() {};		// ������, �Ҹ��ڸ� ���� ȣ������ ���ϰ� �ҰŴ�.
	~Singleton() {};

public:
	static T* GetSingleton();
	void ReleaseSingleton();
};

template<typename T>
T* Singleton<T>::instance = nullptr;

template<typename T>
inline T* Singleton<T>::GetSingleton()
{
	if (!instance)
	{
		instance = new T;
	}
	return instance;
}

template<typename T>
inline void Singleton<T>::ReleaseSingleton()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}
