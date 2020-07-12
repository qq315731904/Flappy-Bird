#pragma once

#include"Scene.h"
#include"Bird.h"
#include"SandDcoin.h"
#include"SandDLives.h"
#include<SDL_keycode.h>
#include "SandDobstacle.h"


class MainScene :public Scene {
private:
	Bird* bird;
	int BGx1 = 0, BGx2 = 960;
	SandDobstacle* obstacleLine = nullptr;	//创建障碍物通道
	SandDLives* livesline = nullptr;	//创建血瓶通道
	SandDcoin* coinline = nullptr;	//创建硬币通道
public:
	using Scene::Scene;
	MainScene();
	~MainScene();
	void update()override;
	void onMouse()override;
	void outMouse()override;
};
