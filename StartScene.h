#pragma once

#include"Scene.h"
#include"MainScene1.h"
#include<SDL_keycode.h>


class StartScene :public Scene {
private:
	int Score;
	int BGx1 = 0, BGx2 = 960;
public:
	using Scene::Scene;
	StartScene();
	~StartScene() = default;
	void update()override;
	void onMouse() override;
	void outMouse()override;
};
