#include "Control.h"
#include "StartScene.h"
#include"EndScene.h"
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <random>
#include <ctime>
#include <cstdlib>
namespace fs = std::filesystem;
extern Control* now;

void Control::Initmypngs(fs::path strPath)
{
	for (auto& fe : fs::directory_iterator(strPath))	//directory_iterator�ǹ���ͨ��Ŀ¼�е��ļ�����������������������
	{
		auto fp = fe.path();
		auto fFiename = fp.filename();
		if (fs::is_directory(fe))	//�Ƿ���·��
		{
			if (fFiename != "." && fFiename != "..")
				Initmypngs(fp);
		}
		else
			if (fs::is_regular_file(fp))	//�Ƿ�����ͨ�ļ�
				now->putImage(fp.generic_string().c_str(), 0, 0, 100, 100);//����ÿ��ͼƬ��С

	}
}
void Control::Initmywavs(fs::path strPath)
{
	for (auto& fe : fs::directory_iterator(strPath))	
	{
		auto fp = fe.path();
		auto fFiename = fp.filename();
		if (fs::is_directory(fe))
		{
			if (fFiename != "." && fFiename != "..")
				Initmywavs(fp);
		}
		else
			if (fs::is_regular_file(fp)) 
			{
				Sounds[fp.generic_string()] = Mix_LoadWAV(fp.generic_string().c_str());
			}

	}
}
/*��ͼƬ�������ļ����м��ش��������������*/

Control::Control(int _width, int _height)
{
	std::srand((int)time(NULL));
	width = _width;
	height = _height;
	SDL_Init(SDL_INIT_EVERYTHING);	//��ʼ��SDL

	window = SDL_CreateWindow("FlappyBird", 0, 0, width, height, SDL_WINDOW_SHOWN);	//��������windows
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);	//����windows���ڴ�����Ⱦ��
	Mix_Init(127);	//����ʹ��OGG, MOD����������WAV������ʽ���ˣ�ʹ��Mix_Init()����ʼ��������
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_CHANNELS, 2048);	//�����ֲ���Ƶ�ʣ����ֲ��Ÿ�ʽ��������������Ч��С��ǰ������ΪĬ�ϣ���������ֲ���Ҳ�����Լ��޸ģ���һ����Ҫ�����Լ��������ļ������޸�
	TTF_Init();	//�����ʼ��
	scene = nullptr;
}
Control::Control() : Control{ 1366, 768 }
{
}

Control::~Control()
{
	for (auto i : Textures)
	{
		SDL_DestroyTexture(i.second);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();

	delete scene;
	scene = nullptr;
}
/*����������ȫ���ÿ�������Ȥ�����˽�*/

void Control::mainLoop()
{
	/*����ͼƬ�����ּ��أ��������������Ȥ�Ŀ����˽�һ�£�����������Բ����*/
	Initmywavs(fs::path{ "./Music" });
	Initmypngs(fs::path{ "./Pic" });


	this->scene = new StartScene();	//������ʼ����
	bool quit = false;
	SDL_Event e;	//�������ռ�����괫������Ϣ

	/*֮����򽫳���ִ��while�������Ķ���ֱ������Ϊ��*/
	while ((!quit)&&(!now->quit))
	{
		Uint64 start = SDL_GetPerformanceCounter();	//64λƽ̨�����ص�ǰ��������ֵ�������˽⣬����Ȥ�����˽�

		while (SDL_PollEvent(&e) != 0)
		{
			/*��ȡ�����Ϣ*/
			now->Mouse_x = e.motion.x;
			now->Mouse_y = e.motion.y;

			/*ѡ��ģʽ0,�ȴ���갴��*/
			if (now->Mouse_x <= 360 && now->Mouse_x >= 100 && now->Mouse_y <= 130 && now->Mouse_y >= 100)
			{
				now->S0_size = 20;
				now->S0 = true;
			}
			else
			{
				now->S0_size = 40;
				now->S0 = false;
			}

			/*ѡ��ģʽ1���ȴ���갴��*/
			if (now->Mouse_x <= 340 && now->Mouse_x >= 100 && now->Mouse_y <= 230 && now->Mouse_y >= 200)
			{
				now->S1_size = 20;
				now->S1 = true;
			}
			else
			{
				now->S1_size = 40;
				now->S1 = false;
			}

			/*ѡ���˳����ȴ���갴��*/
			if (now->Mouse_x <= 180 && now->Mouse_x >= 100 && now->Mouse_y <= 330 && now->Mouse_y >= 300)
			{
				now->Quit_size = 20;
				now->Quit = true;
			}
			else
			{
				now->Quit_size = 40;
				now->Quit = false;
			}

			if (e.type == SDL_QUIT)	//�����x��ťֱ�ӽ�������
			{
				quit = true;
			}

			/*ѡ��ʼ��Ϸ���ȴ���갴��*/
			if (now->Mouse_x <= 450 && now->Mouse_x >= 360 && now->Mouse_y <= 400 && now->Mouse_y >= 320)
			{
				now->Play_size = 50;
			}
			else
			{
				now->Play_size = 100;
			}

			/*������꼴����*/
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				scene->onMouse();	//ִ��onMouse������ע�ⲻͬ������onMouse����
			}

			/*�ɿ���꼴����*/
			if (e.type == SDL_MOUSEBUTTONUP)
			{
				scene->outMouse();
			}
		}
		SDL_RenderClear(renderer);	//�����Ⱦ������Ȥ�����˽�

		/*����뵽��Ӧ��update�����鿴��ʮ����Ҫ*/
		scene->update();	//���볡������ͬ������update������ͬ
		SDL_RenderPresent(renderer);	//��ʼ��Ⱦ������Ȥ�����˽�

		/*����Ȥ�����˽�*/
		Uint64 end = SDL_GetPerformanceCounter();
		float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
		if (elapsedMS < 16.666f)
			SDL_Delay(floor(16.666f - elapsedMS));	//ÿ���˵ĵ������ܶ���һ������ִ���ٶȶ���ͬ�����԰�֡��������60֡���ң��������ʵ��̫��;;Ȳ�����

	}
}

//���ù����
SDL_Renderer* Control::getRenderer()
{
	return renderer;
}

/*ֻҪ������������������Ȥ�����˽�*/
void Control::putImage(std::string path, int x, int y, int width, int height)	//��ͼƬ·����x���꣬y���꣬ͼƬ��ͼƬ����������ʾͼƬ
{
	if (Textures[path] == nullptr)
	{
		SDL_Surface* surface = IMG_Load(path.c_str());
		Textures[path] = SDL_CreateTextureFromSurface(renderer, surface);	//�Ե�ǰͼƬ������Ⱦ
		SDL_FreeSurface(surface);
	}
	auto& texture = Textures[path];
	SDL_Rect box = { x, y, width, height };	//�洢ͼƬλ�ô�С��Ϣ
	SDL_RenderCopy(renderer, texture, NULL, &box);	//���������õ���ȾĿ��
}

int Control::rand() { return std::rand(); }	//����һ���������Ӧ���ø�רҵ�ģ�����Ϊ�˷���

/*���¾����ùܣ�����Ȥ�����˽�*/
void Control::playSound(std::string path, int cnt)
{
	Mix_PlayChannel(-1, Sounds[path], cnt);
}



void Control::xyprintf(int x, int y, const char* c, int size = 20)
{
	if (Fonts.find(size) == Fonts.end())
	{
		Fonts[size] = TTF_OpenFont("./MyFont.ttf", size);	//�������������ttf�ļ��������������Լ���Ҫ�ķ��
	}
	auto& font = Fonts[size];
	SDL_Color color = { 2, 2, 2, 255 };
	SDL_Surface* surface = TTF_RenderText_Blended(font, c, color);
	SDL_Rect box = { x, y, surface->w, surface->h };
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, texture, NULL, &box);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}
