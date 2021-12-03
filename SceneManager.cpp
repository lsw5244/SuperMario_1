#include "SceneManager.h"
#include "GameEntity.h"

GameEntity* SceneManager::currScene = nullptr;
GameEntity* SceneManager::readyScene = nullptr;
GameEntity* SceneManager::loadingScene = nullptr;

DWORD CALLBACK LoadingThread(LPVOID pvParam)
{
	// ������� �ʱ�ȭ�Ѵ�.
	SceneManager::readyScene->Init();
	SceneManager::currScene = SceneManager::readyScene;

	SceneManager::loadingScene->Release();
	SceneManager::loadingScene = nullptr;
	SceneManager::readyScene = nullptr;

	return 0;
}

void SceneManager::Init()
{
}

void SceneManager::Release()
{
	for (map<string, GameEntity*>::iterator it = mapScenes.begin();
		it != mapScenes.end();)
	{
		SAFE_RELEASE(it->second);
		it = mapScenes.erase(it);
	}
	mapScenes.clear();

	for (map<string, GameEntity*>::iterator it = mapLoadingScenes.begin();
		it != mapLoadingScenes.end();)
	{
		SAFE_RELEASE(it->second);
		it = mapLoadingScenes.erase(it);
	}
	mapLoadingScenes.clear();

	//SAFE_RELEASE(currScene);
	SAFE_RELEASE(readyScene);
	SAFE_RELEASE(loadingScene);
}

void SceneManager::Update()
{
	if (currScene)
		currScene->Update();
}

void SceneManager::Render(HDC hdc)
{
	if (currScene)
		currScene->Render(hdc);
}

void SceneManager::AddScene(string key, GameEntity* scene)
{
	if (scene == nullptr)	return;

	if (mapScenes.find(key) != mapScenes.end())
	{
		return;
	}

	mapScenes.insert(pair<string, GameEntity*>(key, scene));

}

void SceneManager::AddLoadingScene(string key, GameEntity* scene)
{
	if (scene == nullptr)	return;

	if (mapLoadingScenes.find(key) != mapLoadingScenes.end())
	{
		return;
	}

	mapLoadingScenes.insert(pair<string, GameEntity*>(key, scene));
}

HRESULT SceneManager::ChangeScene(string sceneName)
{
	map<string, GameEntity*>::iterator it = mapScenes.find(sceneName);

	if (it == mapScenes.end())
		return E_FAIL;

	if (SUCCEEDED((it->second)->Init()))
	{
		if (currScene)
			currScene->Release();

		currScene = it->second;

		return S_OK;
	}

	return E_FAIL;
}

HRESULT SceneManager::ChangeScene(string sceneName, string loadingSceneName)
{
	map<string, GameEntity*>::iterator it = mapScenes.find(sceneName);

	if (it == mapScenes.end())
		return E_FAIL;

	// �ε��� Ȯ��
	map<string, GameEntity*>::iterator itLoading = mapLoadingScenes.find(loadingSceneName);
	if (itLoading == mapLoadingScenes.end())
	{
		return ChangeScene(sceneName);
	}

	// �ε��� ���� ��
	if (SUCCEEDED((itLoading->second)->Init()))
	{
		if (currScene)
			currScene->Release();

		readyScene = it->second;
		loadingScene = itLoading->second;

		currScene = loadingScene;

		// ��Ƽ������ ó��
		DWORD loadThread;
		HANDLE hThread = CreateThread(NULL, 0,
			LoadingThread/*���� ��ų �Լ�������(�Լ��̸�)*/,
			NULL /*���� ��ų �Լ��� �� �Ű�����*/,
			0, &loadThread);

		CloseHandle(hThread);

		return S_OK;
	}

	return E_FAIL;
}
