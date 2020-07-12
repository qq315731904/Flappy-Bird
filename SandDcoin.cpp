#include "SandDcoin.h"
#include "Control.h"
extern Control* now;
void SandDcoin::add(int i)
{
	Coin.push_back(new coin(i));
}
void SandDcoin::drawLine()	//对移出边框的对象进行销毁
{
	for (int j = 0; j < Coin.size(); j++)
	{
		if (Coin[j]->x < -200)
		{
			delete Coin[j];
			Coin.pop_front();
			j--;
		}
	}
	for (auto i : Coin)	//对每一个硬币对象进行绘制
	{
		i->draw();
	}
}
