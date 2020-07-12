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
		/*�����ϰ������ÿִ��50�ξ͸��ݵ�ǰ�ɼ������ϰ����������ɣ�����Խ�����ɿ�����Խ��*/
		time++;
		if (time == 50 && now->is_Pause == false)
		{
			if (now->Score <= 50)	//����<=50ʱ�ϰ�����ּ���Ϊ10%
			{
				int t1 = now->rand() % 100;
				if (t1 >= 90)
				{
					int t = now->rand() % 7;
					obstacleLine->add(t);
				}
			}
			else if (now->Score>50&&now->Score<=250)	//����>50��<=250ʱ�ϰ�����ּ���Ϊ30%
			{
				int t1 = now->rand() % 100;
				if (t1 >= 70)
				{
					int t = now->rand() % 7;
					obstacleLine->add(t);
				}
			}
			else if (now->Score > 250 && now->Score <= 1000)	//����>250��<=1000ʱ�ϰ�����ּ���Ϊ50%
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
				int t1 = now->rand() % 100;	//��������1000ʱ�ϰ�����ּ���Ϊ90%
				if (t1 >= 10)
				{
					int t = now->rand() % 7;
					obstacleLine->add(t);
				}
			}
		}
		if (time == 50)
			time = now->rand() % 30 - now->rand() % 30;	//���Ӹ��������

		/*����Ӳ�ң���Ҫ�����Ա�����޸�*/
		time1++;
		if (time1 == 50 && now->is_Pause == false)	//��Ӳ�ҵ�����Ҫ�󲻴�
		{
			int t = now->rand() % 4;
			coinline->add(t);
		}
		if (time1 == 50)
			time1 = now->rand() % 30 - now->rand() % 30;	//���Ӹ��������

		/*����Ѫƿ������ÿִ��50�ξ͸��ݵ�ǰѪ���������Ѫƿ��Ѫ��Խ��Ѫƿ�����ɸ���Խ��*/
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
			time2 = now->rand() % 30 - now->rand() % 30;	//���Ӹ��������

		/*��ʾ����*/
		obstacleLine->drawLine();	//�ϰ���
		bird->draw();	//��
		livesline->drawLine();	//Ѫƿ
		coinline->drawLine();	//Ӳ��
		//����Hpֵ��ʾѪ��
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

void MainScene::onMouse()
{
		now->playSound("./Music/fly.wav");	//����ɿ�������Ч
		now->is_Mouse = true;
		/*�ж��Ƿ���ͣ*/
		if (now->Mouse_x <= 790 && now->Mouse_x >= 750 && now->Mouse_y <= 40 && now->Mouse_y >= 0 && now->is_Resume)	//�������ͣ��ť��Χ������Ϸ���ڽ���
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
		/*�ж��Ƿ������Ϸ*/
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
		/*�ж��Ƿ�������Ϸ*/
		if (now->Mouse_x <= 640 && now->Mouse_x >= 550 && now->Mouse_y <= 40 && now->Mouse_y >= 0)	//�����������Ϸ��ť�ڣ������now->scene��ΪStartScene����
		{
			now->scene = new StartScene();
			delete this;	//ɾ��MainScene����
			Mix_FreeChunk(now->Sounds["./Music/backgroundmusic.wav"]);
			now->Sounds["./Music/backgroundmusic.wav"] = Mix_LoadWAV("./Music/backgroundmusic.wav");
		}
		if (now->Mouse_x <= 450 && now->Mouse_x >= 360 && now->Mouse_y <= 400 && now->Mouse_y >= 320&&(!now->is_Play))	//�ж��Ƿ��¿�ʼ��
		{
			now->is_Play=true;
		}
}
void MainScene::outMouse()	//�ж�����Ƿ��ɿ�
{
	now->is_Mouse = false;
}


