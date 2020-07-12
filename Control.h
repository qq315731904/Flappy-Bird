#pragma once
#include "Scene.h"
#include "SDL.h"
#include <map>
#include <string>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <filesystem>
namespace fs = std::filesystem;

/*to control the program*/
class Control {
private:
	int width, height;
	//��Ҫ��Ⱦ�Ĵ���
	SDL_Window* window = NULL;	//��������
	SDL_Renderer* renderer = NULL;	//������Ⱦ��
	/*��ֵ������map������ģ���࣬��Ҫ�ؼ��ֺʹ洢��������ģ�����*/
	std::map<std::string, SDL_Texture*>Textures;	//������Ⱦ������
	std::map<int, TTF_Font* >Fonts;	//SDL����û����ʾ���ֵĹ��ܣ���ҪSDL_ttf��չ���е�TTF_Font����������

public:
	std::map<std::string, Mix_Chunk*>Sounds;	//������Ч
	/*ctor,dtor*/
	Control(int _width, int _height);
	Control();
	~Control();
	void mainLoop();	//��ѭ��
	void putImage(std::string path, int x, int y, int width, int height);	//��ʾͼƬ����������Ϊ��·����x��y,ͼƬ��ͼƬ�ߣ�
	void playSound(std::string path, int cnt = 0);	//�������ֺ�����
	void xyprintf(int x, int y, const char* c, int size);	//��ʾ����
	int rand();

	/*��ʼ״̬*/
	int S0_size = 40;	//����ģʽ0ѡ��ͼ���С
	int S1_size = 40;	//����ģʽ1ѡ��ͼ���С
	int S_mode = 0;	//��õ�ǰģʽ��Ĭ��Ϊģʽ0
	int Quit_size = 40;	//�����˳���ť��С
	int Play_size = 100;	//���ƿ�ʼ��Ϸ��ť�Ĵ�С
	int Mouse_x = 0, Mouse_y = 0;	//�������	
	int Bird_dy = 5, Bird_dy1 = 9, Obstacle_dx = 4, coin_dx = 4, Lives_dx = 4;	//С��,�ϰ���,Ӳ�ң�Ѫƿ�ƶ��ٶ�����
	int Bird_y = 430;	//С��y���꣨x����̶�Ϊ100��
	int Hp = 3;	//С��Ѫ������������Ѫ
	int Score = 0;	//�÷�
	int BestScore = 0;	//��߷�
	int cnt = 5;	//С��ɿ�����Ƶ��
	int state = 0;	//����С��ͼƬ��ʾ
	int IF=3;	//�޵�֡


	bool is_HitO = false;	//�ж��Ƿ���ײ�ϰ���
	bool is_HitH = false;	//�ж��Ƿ���ײѪƿ
	bool is_HitC = false;	//�ж��Ƿ���ײӲ��
	bool is_Mouse = false;	//�ж��Ƿ������

	bool is_Play = false;	//�ж��Ƿ�ʼ��Ϸ
	bool S0 = false;	//�ж��Ƿ�ѡ��ģʽ0
	bool S1 = false;	//�ж��Ƿ�ѡ��ģʽ1
	bool Quit = false;	//�ж��Ƿ��˳���Ϸ��quit�����
	bool quit = false;	//�ж��Ƿ��˳���Ϸ
	bool is_Pause = false;	//�ж��Ƿ���ͣ��Ϸ
	bool is_Resume = true;	//�ж��Ƿ�������Ϸ
	bool is_New = false;	//�ж��Ƿ����¿�ʼ��Ϸ

	/*�����ֺ�ͼƬ�ļ����м��غ���*/
	void Initmypngs(fs::path strPath);
	void Initmywavs(fs::path strPath);
	SDL_Renderer* getRenderer();
	Scene* scene;
};

