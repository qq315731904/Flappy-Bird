#include "MainScene1.h"
#include"StartScene.h"
#include "Control.h"
#include <iostream>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "EndScene.h"
#include"Bird.h"
extern Control* now;

MainScene1::MainScene1() {

	char* t = new char[300];
	sprintf(t, "./Music/backgroundmusic.wav");
	now->playSound(t,1000);
	delete[] t;
	now->Hp = 1;
	bird = new Bird();
	obstacleLine = new SandDobstacle();	//�����ϰ���ͨ��
}

MainScene1::~MainScene1() 
{
	delete bird;
	delete obstacleLine;
}
void MainScene1::update() 
{

	if (now->is_Play)	//�ж���Ϸ�Ƿ�ʼ�������ʼ�����ɿ�ʼ
	{
		static int time = 1;
		static int time1 = 1;
		static int time2 = 1;
		now->putImage("./Pic/bg_day.png", BGx1, 0, 960, 640);	//���챳��ͼ
		now->putImage("./Pic/bg_night.png", BGx2, 0, 960, 640);	//ҹ����ͼ
		BGx1 -= 3; BGx2 -= 3;
		if (BGx1 == -960)BGx1 = 960;
		if (BGx2 == -960)BGx2 = 960;
		/*�����ϰ����Ҫ�����Ա�����ʵ��޸�*/
		time++;
		if (time == 50 && now->is_Pause == false)
		{
			int t = now->rand() % 7;
			obstacleLine->add(t);
		}
		if (time == 50)
			time = now->rand() % 30 - now->rand() % 30;

		/*��ʾͼƬ*/
		obstacleLine->drawLine();
		bird->draw();
		/*��ʾ��ͣ��ť*/
		if (now->is_Resume)
		{
			now->putImage("./Pic/button_pause.png", 750, 0, 50, 50);
		}
		/*��ʾ������Ϸ��ť*/
		if (now->is_Pause)
		{
			now->putImage("./Pic/button_resume.png", 700, 0, 50, 50);
		}
		/*��ʾ������Ϸ��ť*/
		if (!now->is_New)
		{
			now->putImage("./Pic/button_menu.png", 550, 0, 100, 50);
		}
		char* v = new char[500];
		sprintf(v, "Score:%d", now->Score);
		now->xyprintf(700, 600, v, 40);
		delete[]v;
	}
	else
	{
		now->putImage("./Pic/bg_day.png", BGx1, 0, 960, 640);	//���챳��ͼ
		now->putImage("./Pic/bg_night.png", BGx2, 0, 960, 640);	//ҹ����ͼ
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

void MainScene1::onMouse()
{
	now->playSound("./Music/fly.wav");	//����ɿ�������Ч
	now->is_Mouse = true;
	/*�ж��Ƿ���ͣ*/
	if (now->Mouse_x <= 840 && now->Mouse_x >= 800 && now->Mouse_y <= 40 && now->Mouse_y >= 0 && now->is_Resume)	//�������ͣ��ť��Χ������Ϸ���ڽ���
	{
		/*���������λ������Ϊ0���ɴﵽ��ͣЧ��*/
		now->is_Pause = true;
		now->is_Resume = false;
		now->Bird_dy = 0;
		now->Bird_dy1 = 0;
		now->Obstacle_dx = 0;
		now->coin_dx = 0;
		now->Lives_dx = 0;
	}
	if (now->Mouse_x <= 740 && now->Mouse_x >= 700 && now->Mouse_y <= 40 && now->Mouse_y >= 0 && now->is_Pause)	//����ڼ�����Ϸ��ť�ڣ�����Ϸ������ͣ״̬
	{
		now->is_Pause = false;
		now->is_Resume = true;
		now->Bird_dy = 5;
		now->Bird_dy1 = 9;
		now->Obstacle_dx = 4;
		now->coin_dx = 4;
		now->Lives_dx = 4;
	}
	if (now->Mouse_x <= 640 && now->Mouse_x >= 550 && now->Mouse_y <= 40 && now->Mouse_y >= 0)	//�����������Ϸ��ť�ڣ������now->scene��ΪStartScene����
	{
		now->scene = new StartScene();
		delete this;	//ɾ��MainScene1����
		Mix_FreeChunk(now->Sounds["./Music/backgroundmusic.wav"]);
		now->Sounds["./Music/backgroundmusic.wav"] = Mix_LoadWAV("./Music/backgroundmusic.wav");
	}
	if (now->Mouse_x <= 450 && now->Mouse_x >= 360 && now->Mouse_y <= 400 && now->Mouse_y >= 320 && (!now->is_Play))	//�ж��Ƿ��¿�ʼ��
	{
		now->is_Play = true;
	}
}
void MainScene1::outMouse()
{
	now->is_Mouse = false;
}


