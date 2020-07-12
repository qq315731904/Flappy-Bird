#include "EndScene.h"
#include "Control.h"
#include<fstream>
#include<iostream>
#include<filesystem>
extern Control* now;
EndScene::EndScene()
{
	Mix_FreeChunk(now->Sounds["./Music/backgroundmusic.wav"]);
	now->Sounds["./Music/backgroundmusic.wav"] = Mix_LoadWAV("./Music/backgroundmusic.wav");
	now->playSound("./Music/gameovermusic.wav");
	WriteFile();
	ReadFile();

}

void EndScene::update()
{
	now->putImage("./Pic/bg_day.png", BGx1, 0, 960, 640);
	now->putImage("./Pic/text_game_over.png", 230, 0, 400, 200);
	now->putImage("./Pic/score_panel.png", 250, 250, 400, 200);
	now->putImage("./Pic/button_play.png", 300, 450, 100, 50);
	now->putImage("./Pic/button_menu.png", 450, 450, 100, 50);
	if (now->Score <= 50)
	{
		now->putImage("./Pic/medals_3.png", 300, 320, 80, 80);
	}
	else if (now->Score > 50 && now->Score <= 250)
	{
		now->putImage("./Pic/medals_2.png", 300, 320, 80, 80);
	}
	else if (now->Score > 250 && now->Score <= 1000)
	{
		now->putImage("./Pic/medals_1.png", 300, 320, 80, 80);
	}
	else
	now->putImage("./Pic/medals_0.png", 300, 320, 80, 80);


	/*当前成绩*/
	char* x = new char[500];
	sprintf(x, "%d",now->Score);
	now->xyprintf(500, 300, x, 40);
	delete[]x;

	/*最高成绩*/
	char* y = new char[500];
	sprintf(y, "%d", now->BestScore);
	now->xyprintf(500, 370, y, 40);
	delete[]y;
}



void EndScene::onMouse()
{
	/*判断是否重新开始当前模式*/
	if (now->Mouse_x <= 390 && now->Mouse_x >= 300 && now->Mouse_y <= 490 && now->Mouse_y >= 450)
	{
		switch (now->S_mode)
		{
		case 0:
			now->scene = new MainScene();
			delete this;
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
			break;
		case 1:
			now->scene = new MainScene1();
			delete this;
			/*恢复初始值*/
			now->S0_size = 40;	//控制模式0选项图标大小
			now->S1_size = 40;	//控制模式1选项图标大小
			now->S_mode = 1;	//获得当前模式，默认为模式0
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
			now->Hp = 1;	//小鸟血量，假设三条血
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
			break;
		}
	}
	/*判断是否返回菜单*/
	if (now->Mouse_x <= 540 && now->Mouse_x >= 450 && now->Mouse_y <= 490 && now->Mouse_y >= 450)
	{
		now->scene = new StartScene();
		delete this;
	}
}
void EndScene::outMouse()
{
}

void EndScene::WriteFile()
{
	std::filesystem::path p{ "./Score.txt" };
	std::ofstream input(p, std::ios::app);

	input << now->Score << "\n";
	input.close();

}

void EndScene::ReadFile()
{
	int array[1000];
	int* ptr = &array[0];
	std::ifstream output;
	output.open("./Score.txt");
	if (!output.is_open())
	{
		now->xyprintf(500, 500, "无法打开文件",40);
		exit(EXIT_FAILURE);
	}
	int i = 0;
	while (!output.eof())
	{
		output >> *ptr;
		ptr++;
		i++;
	}
	for (int j=0; j < i; j++)
	{
		if (now->BestScore < array[j])
		{
			now->BestScore = array[j];
		}
	}
	output.close();
}