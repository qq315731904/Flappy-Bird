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
	//将要渲染的窗口
	SDL_Window* window = NULL;	//创建窗口
	SDL_Renderer* renderer = NULL;	//创建渲染器
	/*键值对容器map对象是模板类，需要关键字和存储对象两个模板参数*/
	std::map<std::string, SDL_Texture*>Textures;	//创建渲染器容器
	std::map<int, TTF_Font* >Fonts;	//SDL本身没有显示文字的功能，需要SDL_ttf拓展库中的TTF_Font函数打开字体

public:
	std::map<std::string, Mix_Chunk*>Sounds;	//播放音效
	/*ctor,dtor*/
	Control(int _width, int _height);
	Control();
	~Control();
	void mainLoop();	//主循环
	void putImage(std::string path, int x, int y, int width, int height);	//显示图片函数，参数为（路径，x，y,图片宽，图片高）
	void playSound(std::string path, int cnt = 0);	//播放音乐函数，
	void xyprintf(int x, int y, const char* c, int size);	//显示文字
	int rand();

	/*初始状态*/
	int S0_size = 40;	//控制模式0选项图标大小
	int S1_size = 40;	//控制模式1选项图标大小
	int S_mode = 0;	//获得当前模式，默认为模式0
	int Quit_size = 40;	//控制退出按钮大小
	int Play_size = 100;	//控制开始游戏按钮的大小
	int Mouse_x = 0, Mouse_y = 0;	//鼠标坐标	
	int Bird_dy = 5, Bird_dy1 = 9, Obstacle_dx = 4, coin_dx = 4, Lives_dx = 4;	//小鸟,障碍物,硬币，血瓶移动速度数据
	int Bird_y = 430;	//小鸟y坐标（x坐标固定为100）
	int Hp = 3;	//小鸟血量，假设三条血
	int Score = 0;	//得分
	int BestScore = 0;	//最高分
	int cnt = 5;	//小鸟煽动翅膀频率
	int state = 0;	//控制小鸟图片显示
	int IF=3;	//无敌帧


	bool is_HitO = false;	//判断是否碰撞障碍物
	bool is_HitH = false;	//判断是否碰撞血瓶
	bool is_HitC = false;	//判断是否碰撞硬币
	bool is_Mouse = false;	//判断是否点击鼠标

	bool is_Play = false;	//判断是否开始游戏
	bool S0 = false;	//判断是否选择模式0
	bool S1 = false;	//判断是否选择模式1
	bool Quit = false;	//判断是否退出游戏和quit相关联
	bool quit = false;	//判断是否退出游戏
	bool is_Pause = false;	//判断是否暂停游戏
	bool is_Resume = true;	//判断是否启动游戏
	bool is_New = false;	//判断是否重新开始游戏

	/*对音乐和图片文件进行加载函数*/
	void Initmypngs(fs::path strPath);
	void Initmywavs(fs::path strPath);
	SDL_Renderer* getRenderer();
	Scene* scene;
};

