#pragma once
#include "coin.h"
#include<deque>
class SandDcoin
{
public:
	std::deque<coin*>Coin;	//��������
	SandDcoin() = default;
	void add(int i);// ��һ������������1�����ϰ�DownObstacle.png��2�����ϰ�LeftObstacle.png��3����RightObstaclepng
	void drawLine();
};