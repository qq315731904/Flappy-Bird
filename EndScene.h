#pragma once

#include"Scene.h"
#include"MainScene.h"
#include"StartScene.h"
#include<SDL_keycode.h>


class EndScene :public Scene
{
private:
public:
	int BGx1 = 0, BGx2 = 960;
	using Scene::Scene;
	EndScene();
	~EndScene() = default;
	void update()override;
	void onMouse()override;
	void outMouse()override;
	void WriteFile();	//д�ļ�
	void ReadFile();	//���ļ�
};
