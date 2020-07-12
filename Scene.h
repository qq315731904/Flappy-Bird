#pragma once
#include<SDL_keycode.h>
class Scene {
public:
	Scene() = default;
	virtual void update() = 0;
	virtual void onMouse() = 0;
	virtual void outMouse() = 0;
};
