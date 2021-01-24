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

	//¾ÀÃß°¡ ÇÔ¼ö
	gameNode* addScene(string sceneName, gameNode* scene);

	//¾À º¯°æ ÇÔ¼ö
	HRESULT changeScene(string sceneName);

	sceneManager() {};
	~sceneManager() {};
};

