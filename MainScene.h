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
	SandDobstacle* obstacleLine = nullptr;	//�����ϰ���ͨ��
	SandDLives* livesline = nullptr;	//����Ѫƿͨ��
	SandDcoin* coinline = nullptr;	//����Ӳ��ͨ��
public:
	using Scene::Scene;
	MainScene();
	~MainScene();
	void update()override;
	void onMouse()override;
	void outMouse()override;
};
