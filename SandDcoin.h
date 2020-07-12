#pragma once
#include "coin.h"
#include<deque>
class SandDcoin
{
public:
	std::deque<coin*>Coin;	//创建容器
	SandDcoin() = default;
	void add(int i);// 传一个整数参数，1代表障碍DownObstacle.png，2代表障碍LeftObstacle.png，3代表RightObstaclepng
	void drawLine();
};