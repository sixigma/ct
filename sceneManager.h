#pragma once
#include "singleton.h"
#include <string>
#include <map>

class gameNode;

class sceneManager : public singleton<sceneManager>
{
public:
	typedef map<string, gameNode*> sceneList;
	typedef map<string, gameNode*>::iterator sceneIter;

private:
	static gameNode* _currentScene;

	sceneList _sceneList;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//씬추가 함수
	gameNode* addScene(string sceneName, gameNode* scene);

	//씬 변경 함수
	HRESULT changeScene(string sceneName);

	sceneManager() {};
	~sceneManager() {};
};

