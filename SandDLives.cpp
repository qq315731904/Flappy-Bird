#include "SandDLives.h"
#include "Control.h"
extern Control* now;
void SandDLives::add(int i)
{
	lives.push_back(new Lives(i));
}
void SandDLives::drawLine()
{
	for (int j = 0; j < lives.size(); j++)	//���Ƴ��߿�Ķ����������
	{
		if (lives[j]->x < -200)
		{
			delete lives[j];
			lives.pop_front();
			j--;
		}
	}
	for (auto i : lives)	//��ÿһ��Ѫƿ������л���
	{
		i->draw();
	}
}
