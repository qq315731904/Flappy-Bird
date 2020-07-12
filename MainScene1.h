#pragma once
#include"Scene.h"
#include"Bird.h"
#include"SandDcoin.h"
#include"SandDLives.h"
#include<SDL_keycode.h>
#include "SandDobstacle.h"


class MainScene1 :public Scene {
private:
	Bird* bird;
	int BGx1 = 0, BGx2 = 960;
	SandDobstacle* obstacleLine = nullptr;
	//SandDLives* livesline = nullptr;
	//SandDcoin* coinline = nullptr;
public:
	using Scene::Scene;
	MainScene1();
	~MainScene1();
	void update()override;
	void onMouse()override;
	void outMouse()override;
};


