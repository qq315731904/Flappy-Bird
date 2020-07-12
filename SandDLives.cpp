#include "SandDLives.h"
#include "Control.h"
extern Control* now;
void SandDLives::add(int i)
{
	lives.push_back(new Lives(i));
}
void SandDLives::drawLine()
{
	for (int j = 0; j < lives.size(); j++)	//对移出边框的对象进行销毁
	{
		if (lives[j]->x < -200)
		{
			delete lives[j];
			lives.pop_front();
			j--;
		}
	}
	for (auto i : lives)	//对每一个血瓶对象进行绘制
	{
		i->draw();
	}
}
