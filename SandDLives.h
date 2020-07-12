#pragma once
#include "Lives.h"
#include<deque>
class SandDLives
{
public:
	std::deque<Lives*>lives;	//创建容器
	SandDLives() = default;
	void add(int i);// 传一个整数参数选择障碍类型
	void drawLine();
};