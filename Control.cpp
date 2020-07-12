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
	for (auto& fe : fs::directory_iterator(strPath))	//directory_iterator是构造通过目录中的文件名进行排序的输入迭代器。
	{
		auto fp = fe.path();
		auto fFiename = fp.filename();
		if (fs::is_directory(fe))	//是否是路径
		{
			if (fFiename != "." && fFiename != "..")
				Initmypngs(fp);
		}
		else
			if (fs::is_regular_file(fp))	//是否是普通文件
				now->putImage(fp.generic_string().c_str(), 0, 0, 100, 100);//设置每张图片大小

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
/*对图片和音乐文件进行加载处理，方便后续调用*/

Control::Control(int _width, int _height)
{
	std::srand((int)time(NULL));
	width = _width;
	height = _height;
	SDL_Init(SDL_INIT_EVERYTHING);	//初始化SDL

	window = SDL_CreateWindow("FlappyBird", 0, 0, width, height, SDL_WINDOW_SHOWN);	//创建窗口windows
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);	//基于windows窗口创建渲染器
	Mix_Init(127);	//对于使用OGG, MOD或者其他非WAV声音格式的人，使用Mix_Init()来初始化解码器
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_CHANNELS, 2048);	//（音乐播放频率，音乐播放格式，播放声道，音效大小）前三个均为默认（如果会音乐播放也可以自己修改）后一个需要根据自己的音乐文件进行修改
	TTF_Init();	//字体初始化
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
/*以上内容完全不用看，有兴趣可以了解*/

void Control::mainLoop()
{
	/*进行图片和音乐加载，里面的内容有兴趣的可以了解一下，其他情况可以不理会*/
	Initmywavs(fs::path{ "./Music" });
	Initmypngs(fs::path{ "./Pic" });


	this->scene = new StartScene();	//创建开始场景
	bool quit = false;
	SDL_Event e;	//用来接收键盘鼠标传来的信息

	/*之后程序将持续执行while语句里面的东西直至条件为假*/
	while ((!quit)&&(!now->quit))
	{
		Uint64 start = SDL_GetPerformanceCounter();	//64位平台，返回当前计数器的值，无需了解，有兴趣可以了解

		while (SDL_PollEvent(&e) != 0)
		{
			/*获取鼠标信息*/
			now->Mouse_x = e.motion.x;
			now->Mouse_y = e.motion.y;

			/*选择模式0,等待鼠标按下*/
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

			/*选择模式1，等待鼠标按下*/
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

			/*选择退出，等待鼠标按下*/
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

			if (e.type == SDL_QUIT)	//即点击x按钮直接结束程序
			{
				quit = true;
			}

			/*选择开始游戏，等待鼠标按下*/
			if (now->Mouse_x <= 450 && now->Mouse_x >= 360 && now->Mouse_y <= 400 && now->Mouse_y >= 320)
			{
				now->Play_size = 50;
			}
			else
			{
				now->Play_size = 100;
			}

			/*按下鼠标即进行*/
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				scene->onMouse();	//执行onMouse函数，注意不同场景的onMouse函数
			}

			/*松开鼠标即进行*/
			if (e.type == SDL_MOUSEBUTTONUP)
			{
				scene->outMouse();
			}
		}
		SDL_RenderClear(renderer);	//清除渲染，有兴趣可以了解

		/*请进入到对应的update函数查看，十分重要*/
		scene->update();	//进入场景，不同场景的update函数不同
		SDL_RenderPresent(renderer);	//开始渲染，有兴趣可以了解

		/*有兴趣可以了解*/
		Uint64 end = SDL_GetPerformanceCounter();
		float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
		if (elapsedMS < 16.666f)
			SDL_Delay(floor(16.666f - elapsedMS));	//每个人的电脑性能都不一样程序执行速度都不同，所以把帧数控制在60帧左右，如果性能实在太差就就救不了了

	}
}

//不用管这个
SDL_Renderer* Control::getRenderer()
{
	return renderer;
}

/*只要求会用这个函数，有兴趣可以了解*/
void Control::putImage(std::string path, int x, int y, int width, int height)	//（图片路径，x坐标，y坐标，图片宽，图片长）用来显示图片
{
	if (Textures[path] == nullptr)
	{
		SDL_Surface* surface = IMG_Load(path.c_str());
		Textures[path] = SDL_CreateTextureFromSurface(renderer, surface);	//对当前图片进行渲染
		SDL_FreeSurface(surface);
	}
	auto& texture = Textures[path];
	SDL_Rect box = { x, y, width, height };	//存储图片位置大小信息
	SDL_RenderCopy(renderer, texture, NULL, &box);	//将纹理设置到渲染目标
}

int Control::rand() { return std::rand(); }	//设置一个随机数，应该用更专业的，但是为了方便

/*以下均不用管，有兴趣可以了解*/
void Control::playSound(std::string path, int cnt)
{
	Mix_PlayChannel(-1, Sounds[path], cnt);
}



void Control::xyprintf(int x, int y, const char* c, int size = 20)
{
	if (Fonts.find(size) == Fonts.end())
	{
		Fonts[size] = TTF_OpenFont("./MyFont.ttf", size);	//设置字体风格，这个ttf文件可以上网下载自己想要的风格
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
