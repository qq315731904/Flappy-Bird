#include "StartScene.h"
#include "Control.h"
#include "MainScene.h"
#include "SDL_events.h"
extern Control* now;
StartScene::StartScene()
{
	/*�ָ���ʼֵ*/
	now->S0_size = 40;	//����ģʽ0ѡ��ͼ���С
	now->S1_size = 40;	//����ģʽ1ѡ��ͼ���С
	now->S_mode = 0;	//��õ�ǰģʽ��Ĭ��Ϊģʽ0
	now->Quit_size = 40;	//�����˳���ť��С
	now->Play_size = 100;	//���ƿ�ʼ��Ϸ��ť�Ĵ�С
	now->Mouse_x = 0;
	now->Mouse_y = 0;	//�������	
	now->Bird_dy = 5;
	now->Bird_dy1 = 9;
	now->Obstacle_dx = 4;
	now->coin_dx = 4;
	now->Lives_dx = 4;	//С��,�ϰ���,Ӳ�ң�Ѫƿ�ƶ��ٶ�����
	now->Bird_y = 430;	//С��y���꣨x����̶�Ϊ100��
	now->Hp = 3;	//С��Ѫ������������Ѫ
	now->Score = 0;	//�÷�
	now->cnt = 5;	//С��ɿ�����Ƶ��
	now->state = 0;
	now->BestScore = 0;
	now->IF = 0;

	now->is_HitO = false;	//�ж��Ƿ���ײ�ϰ���
	now->is_HitH = false;	//�ж��Ƿ���ײѪƿ
	now->is_HitC = false;	//�ж��Ƿ���ײӲ��
	now->is_Mouse = false;	//�ж��Ƿ������

	now->is_Play = false;	//�ж��Ƿ�ʼ��Ϸ
	now->S0 = false;	//�ж��Ƿ�ѡ��ģʽ0
	now->S1 = false;	//�ж��Ƿ�ѡ��ģʽ1
	now->Quit = false;	//�ж��Ƿ��˳���Ϸ��quit�����
	now->quit = false;	//�ж��Ƿ��˳���Ϸ
	now->is_Pause = false;	//�ж��Ƿ���ͣ��Ϸ
	now->is_Resume = true;	//�ж��Ƿ�������Ϸ
	now->is_New = false;	//�ж��Ƿ����¿�ʼ��Ϸ
}
void StartScene::update()
{
	/*����*/
	now->putImage("./Pic/bg_day.png", BGx1, 0, 960, 640);
	now->putImage("./Pic/bg_night.png", BGx2, 0, 960, 640);
	BGx1 -= 3; BGx2 -= 3;
	if (BGx1 == -960)BGx1 = 960;
	if (BGx2 == -960)BGx2 = 960;

	/*ģʽѡ��*/
	char* s = new char[500];
	sprintf(s, "Prop mode");	
	now->xyprintf(100, 100, s, now->S0_size);
	now->xyprintf(100, 200, "Classic mode", now->S1_size);
	now->xyprintf(100, 300, "Quit", now->Quit_size);
	delete[]s;

	/*��Ϸ����ͼ��*/
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
	//����ģʽ0
	if (now->S0)
	{
		now->is_New = false;
		now->S_mode = 0;
		now->scene = new MainScene();	//������Ϸ���г������˺��ΪMainScene����ֱ������Ϸ��ѡ��������Ϸ
		delete this;	//ɾ����ʼ����
	}
	//����ģʽ1
	if (now->S1)
	{
		delete now->scene;	//ɾ����ʼ����
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
