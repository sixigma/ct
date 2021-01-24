#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

gameNode* sceneManager::_currentScene = NULL;

HRESULT sceneManager::init()
{
	_currentScene = NULL;

	return S_OK;
}

void sceneManager::release()
{
	sceneIter miSceneList = _sceneList.begin();

	for (; miSceneList != _sceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->release();
			SAFE_DEL(miSceneList->second);
			miSceneList = _sceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}
	_sceneList.clear();
}

void sceneManager::update()
{
	if (_currentScene) _currentScene->update();
}

void sceneManager::render()
{
	if (_currentScene) _currentScene->render();
}

gameNode* sceneManager::addScene(string sceneName, gameNode* scene)
{
	if (!scene) return nullptr;

	_sceneList.insert(make_pair(sceneName, scene));

	return scene;
}


HRESULT sceneManager::changeScene(string sceneName)
{
	sceneIter find = _sceneList.find(sceneName);
	if (find == _sceneList.end()) return E_FAIL;
	if (find->second == _currentScene) return S_OK;
	if (SUCCEEDED(find->second->init()))
	{
		if (_currentScene) _currentScene->release();
		_currentScene = find->second;
		return S_OK;
	}
	return E_FAIL;
}
