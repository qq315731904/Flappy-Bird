#pragma once
#include "Obstacle.h"
#include<deque>
class SandDobstacle
{
public:
	std::deque<Obstacle*>obstacle;	//��������
	SandDobstacle() = default;
	void add(int i);// ��һ����������ѡ���ϰ�����
	void drawLine();
};