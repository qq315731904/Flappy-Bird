#pragma once
#include "Lives.h"
#include<deque>
class SandDLives
{
public:
	std::deque<Lives*>lives;	//��������
	SandDLives() = default;
	void add(int i);// ��һ����������ѡ���ϰ�����
	void drawLine();
};