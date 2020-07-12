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


	/*��ǰ�ɼ�*/
	char* x = new char[500];
	sprintf(x, "%d",now->Score);
	now->xyprintf(500, 300, x, 40);
	delete[]x;

	/*��߳ɼ�*/
	char* y = new char[500];
	sprintf(y, "%d", now->BestScore);
	now->xyprintf(500, 370, y, 40);
	delete[]y;
}



void EndScene::onMouse()
{
	/*�ж��Ƿ����¿�ʼ��ǰģʽ*/
	if (now->Mouse_x <= 390 && now->Mouse_x >= 300 && now->Mouse_y <= 490 && now->Mouse_y >= 450)
	{
		switch (now->S_mode)
		{
		case 0:
			now->scene = new MainScene();
			delete this;
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
			break;
		case 1:
			now->scene = new MainScene1();
			delete this;
			/*�ָ���ʼֵ*/
			now->S0_size = 40;	//����ģʽ0ѡ��ͼ���С
			now->S1_size = 40;	//����ģʽ1ѡ��ͼ���С
			now->S_mode = 1;	//��õ�ǰģʽ��Ĭ��Ϊģʽ0
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
			now->Hp = 1;	//С��Ѫ������������Ѫ
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
			break;
		}
	}
	/*�ж��Ƿ񷵻ز˵�*/
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
		now->xyprintf(500, 500, "�޷����ļ�",40);
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