#include "StartScene.h"
#include "Control.h"
#include "MainScene.h"
#include "SDL_events.h"
extern Control* now;
StartScene::StartScene()
{
	/*恢复初始值*/
	now->S0_size = 40;	//控制模式0选项图标大小
	now->S1_size = 40;	//控制模式1选项图标大小
	now->S_mode = 0;	//获得当前模式，默认为模式0
	now->Quit_size = 40;	//控制退出按钮大小
	now->Play_size = 100;	//控制开始游戏按钮的大小
	now->Mouse_x = 0;
	now->Mouse_y = 0;	//鼠标坐标	
	now->Bird_dy = 5;
	now->Bird_dy1 = 9;
	now->Obstacle_dx = 4;
	now->coin_dx = 4;
	now->Lives_dx = 4;	//小鸟,障碍物,硬币，血瓶移动速度数据
	now->Bird_y = 430;	//小鸟y坐标（x坐标固定为100）
	now->Hp = 3;	//小鸟血量，假设三条血
	now->Score = 0;	//得分
	now->cnt = 5;	//小鸟煽动翅膀频率
	now->state = 0;
	now->BestScore = 0;
	now->IF = 0;

	now->is_HitO = false;	//判断是否碰撞障碍物
	now->is_HitH = false;	//判断是否碰撞血瓶
	now->is_HitC = false;	//判断是否碰撞硬币
	now->is_Mouse = false;	//判断是否点击鼠标

	now->is_Play = false;	//判断是否开始游戏
	now->S0 = false;	//判断是否选择模式0
	now->S1 = false;	//判断是否选择模式1
	now->Quit = false;	//判断是否退出游戏和quit相关联
	now->quit = false;	//判断是否退出游戏
	now->is_Pause = false;	//判断是否暂停游戏
	now->is_Resume = true;	//判断是否启动游戏
	now->is_New = false;	//判断是否重新开始游戏
}
void StartScene::update()
{
	/*背景*/
	now->putImage("./Pic/bg_day.png", BGx1, 0, 960, 640);
	now->putImage("./Pic/bg_night.png", BGx2, 0, 960, 640);
	BGx1 -= 3; BGx2 -= 3;
	if (BGx1 == -960)BGx1 = 960;
	if (BGx2 == -960)BGx2 = 960;

	/*模式选项*/
	char* s = new char[500];
	sprintf(s, "Prop mode");	
	now->xyprintf(100, 100, s, now->S0_size);
	now->xyprintf(100, 200, "Classic mode", now->S1_size);
	now->xyprintf(100, 300, "Quit", now->Quit_size);
	delete[]s;

	/*游戏其他图标*/
	now->putImage("./Pic/title.png", 360,0, 200, 100);
	char* x = new char[500];
	sprintf(x, "./Pic/bird0_%d.png", now->state / now->cnt);
	now->putImage(x, 360, 320, 100, 100);
	now->state++;
	if (now->state == now->cnt * 3)now->state = 0;
	delete[] x;
}

void StartScene::onMouse()
{
	//进入模式0
	if (now->S0)
	{
		now->is_New = false;
		now->S_mode = 0;
		now->scene = new MainScene();	//创建游戏运行场景，此后均为MainScene场景直至在游戏中选择重新游戏
		delete this;	//删除开始场景
	}
	//进入模式1
	if (now->S1)
	{
		delete now->scene;	//删除开始场景
		now->S_mode = 1;
		now->is_New = false;
		now->scene = new MainScene1();

	}
	if (now->Quit)
	{
		now->quit = true;
	}
}
void StartScene::outMouse()
{
}
