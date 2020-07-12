#include "MainScene.h"
#include"StartScene.h"
#include "Control.h"
#include <iostream>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "EndScene.h"
#include"Bird.h"
extern Control* now;

MainScene::MainScene() 
{

	char* t = new char[300];
	sprintf(t, "./Music/backgroundmusic.wav");
	now->playSound(t,1000);
	delete[] t;
	bird = new Bird();
	obstacleLine = new SandDobstacle();
	livesline = new SandDLives();
	coinline = new SandDcoin();
}

MainScene::~MainScene() 
{
	delete bird;
	delete obstacleLine;
	delete livesline;
	delete coinline;
}
void MainScene::update()
{
	if (now->is_Play)	//判断游戏是否开始，点击开始键即可开始
	{
		static int time = 1;
		static int time1 = 1;
		static int time2 = 1;
		now->putImage("./Pic/bg_day.png", BGx1, 0, 960, 640);	//白天背景图
		now->putImage("./Pic/bg_night.png", BGx2, 0, 960, 640);	//夜晚背景图
		BGx1 -= 3; BGx2 -= 3;
		if (BGx1 == -960)BGx1 = 960;
		if (BGx2 == -960)BGx2 = 960;
		/*生成障碍物，程序每执行50次就根据当前成绩进行障碍物的随机生成，分数越高生成可能性越大*/
		time++;
		if (time == 50 && now->is_Pause == false)
		{
			if (now->Score <= 50)	//分数<=50时障碍物出现几率为10%
			{
				int t1 = now->rand() % 100;
				if (t1 >= 90)
				{
					int t = now->rand() % 7;
					obstacleLine->add(t);
				}
			}
			else if (now->Score>50&&now->Score<=250)	//分数>50且<=250时障碍物出现几率为30%
			{
				int t1 = now->rand() % 100;
				if (t1 >= 70)
				{
					int t = now->rand() % 7;
					obstacleLine->add(t);
				}
			}
			else if (now->Score > 250 && now->Score <= 1000)	//分数>250且<=1000时障碍物出现几率为50%
			{
				int t1 = now->rand() % 100;
				if (t1 >= 50)
				{
					int t = now->rand() % 7;
					obstacleLine->add(t);
				}
			}
			else
			{
				int t1 = now->rand() % 100;	//分数超过1000时障碍物出现几率为90%
				if (t1 >= 10)
				{
					int t = now->rand() % 7;
					obstacleLine->add(t);
				}
			}
		}
		if (time == 50)
			time = now->rand() % 30 - now->rand() % 30;	//增加更多随机性

		/*生成硬币，需要相关人员进行修改*/
		time1++;
		if (time1 == 50 && now->is_Pause == false)	//对硬币的生成要求不大
		{
			int t = now->rand() % 4;
			coinline->add(t);
		}
		if (time1 == 50)
			time1 = now->rand() % 30 - now->rand() % 30;	//增加更多随机性

		/*生成血瓶，程序每执行50次就根据当前血量情况生成血瓶，血量越低血瓶的生成概率越大*/
		time2++;
		if (time2 == 50 && now->is_Pause == false)
		{
			int t1 = now->rand() % 640;
			if (now->Hp == 3)
			{
				int t = 0;
				t = rand() * 100 / (RAND_MAX + 1);
				if (t < 10)
				{
					livesline->add(t1);
				}
			}
			if (now->Hp == 2)
			{
				int t = 0;
				t = rand() * 100 / (RAND_MAX + 1);
				if (t < 20)
				{
					livesline->add(t1);
				}
			}
			if (now->Hp == 1)
			{
				int t = 0;
				t = rand() * 100 / (RAND_MAX + 1);
				if (t < 50)
				{
					livesline->add(t1);
				}
			}

		}
		if (time2 == 50)
			time2 = now->rand() % 30 - now->rand() % 30;	//增加更多随机性

		/*显示动画*/
		obstacleLine->drawLine();	//障碍物
		bird->draw();	//鸟
		livesline->drawLine();	//血瓶
		coinline->drawLine();	//硬币
		//根据Hp值显示血量
		if (now->Hp == 3)
		{
			now->putImage("./Pic/Lives.png", 0, 0, 50, 50);
			now->putImage("./Pic/Lives.png", 50, 0, 50, 50);
			now->putImage("./Pic/Lives.png", 100, 0, 50, 50);
		}
		if (now->Hp == 2)
		{
			now->putImage("./Pic/Lives.png", 0, 0, 50, 50);
			now->putImage("./Pic/Lives.png", 50, 0, 50, 50);
		}
		if (now->Hp == 1)
		{
			now->putImage("./Pic/Lives.png", 0, 0, 50, 50);
		}
		char* v = new char[500];
		sprintf(v, "Score:%d", now->Score);
		now->xyprintf(700, 600, v, 40);
		delete[]v;
		if (now->is_Resume)
		{
			now->putImage("./Pic/button_pause.png", 750, 0, 50, 50);
		}
		/*显示继续游戏按钮*/
		if (now->is_Pause)
		{
			now->putImage("./Pic/button_resume.png", 700, 0, 50, 50);
		}
		/*显示重新游戏按钮*/
		if (!now->is_New)
		{
			now->putImage("./Pic/button_menu.png", 550, 0, 100, 50);
		}
	}
	else
	{
		now->putImage("./Pic/bg_day.png", BGx1, 0, 960, 640);	//白天背景图
		now->putImage("./Pic/bg_night.png", BGx2, 0, 960, 640);	//夜晚背景图
		BGx1 -= 3; BGx2 -= 3;
		if (BGx1 == -960)BGx1 = 960;
		if (BGx2 == -960)BGx2 = 960;

		char* x = new char[500];
		sprintf(x, "./Pic/bird0_%d.png", now->state / now->cnt);
		now->putImage(x, 100, 430, 100, 100);
		now->state++;

		if (now->state == now->cnt * 3)now->state = 0;
		delete[] x;
		now->putImage("./Pic/button_play.png", 360, 320, now->Play_size, now->Play_size);

	}
	if (now->Hp <= 0)
	{
		now->scene = new EndScene();
		delete this;
	}
}

void MainScene::onMouse()
{
		now->playSound("./Music/fly.wav");	//播放煽动翅膀音效
		now->is_Mouse = true;
		/*判断是否暂停*/
		if (now->Mouse_x <= 790 && now->Mouse_x >= 750 && now->Mouse_y <= 40 && now->Mouse_y >= 0 && now->is_Resume)	//鼠标在暂停按钮范围内且游戏正在进行
		{
			/*将各物体的位移量设为0即可达到暂停效果*/
			now->is_Pause = true;
			now->is_Resume = false;
			now->Bird_dy = 0; 
			now->Bird_dy1 = 0;
			now->Obstacle_dx = 0;
			now->coin_dx = 0;
			now->Lives_dx = 0;
		}
		/*判断是否继续游戏*/
		if (now->Mouse_x <= 740 && now->Mouse_x >= 700 && now->Mouse_y <= 40 && now->Mouse_y >= 0 && now->is_Pause)	//鼠标在继续游戏按钮内，且游戏处于暂停状态
		{
			now->is_Pause = false;
			now->is_Resume = true;
			now->Bird_dy = 5;
			now->Bird_dy1 = 9;
			now->Obstacle_dx = 4;
			now->coin_dx = 4;
			now->Lives_dx = 4;
		}
		/*判断是否重新游戏*/
		if (now->Mouse_x <= 640 && now->Mouse_x >= 550 && now->Mouse_y <= 40 && now->Mouse_y >= 0)	//鼠标在重新游戏按钮内，点击后now->scene变为StartScene场景
		{
			now->scene = new StartScene();
			delete this;	//删除MainScene场景
			Mix_FreeChunk(now->Sounds["./Music/backgroundmusic.wav"]);
			now->Sounds["./Music/backgroundmusic.wav"] = Mix_LoadWAV("./Music/backgroundmusic.wav");
		}
		if (now->Mouse_x <= 450 && now->Mouse_x >= 360 && now->Mouse_y <= 400 && now->Mouse_y >= 320&&(!now->is_Play))	//判断是否按下开始键
		{
			now->is_Play=true;
		}
}
void MainScene::outMouse()	//判断鼠标是否松开
{
	now->is_Mouse = false;
}


