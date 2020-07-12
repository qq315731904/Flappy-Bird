#include"Control.h"
#include<SDL.h>
Control* now = nullptr;
int main(int argc, char* argv[]) 
{
	now = new Control(960, 640);
	now->mainLoop();	//从这里开始进入游戏
	delete now;
	return 0;
}