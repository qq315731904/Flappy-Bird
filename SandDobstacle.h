#pragma once
#include "Obstacle.h"
#include<deque>
class SandDobstacle
{
public:
	std::deque<Obstacle*>obstacle;	//创建容器
	SandDobstacle() = default;
	void add(int i);// 传一个整数参数选择障碍类型
	void drawLine();
};