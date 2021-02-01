#pragma once
#include "gameNode.h"
#include "player.h"

constexpr int VIEWPORT_UPDATE_OFFSET = 2;

class gameScene : public gameNode
{
private:
	static int _countForReEnablingKeyInput;
	player* _p;


public:
	gameScene() = default;
	gameScene(int anyNum);
	~gameScene() override;

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	void updateViewport(int x, int y);
	void setViewport(int x, int y);
};

