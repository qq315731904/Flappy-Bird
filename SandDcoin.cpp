#include "SandDcoin.h"
#include "Control.h"
extern Control* now;
void SandDcoin::add(int i)
{
	Coin.push_back(new coin(i));
}
void SandDcoin::drawLine()	//���Ƴ��߿�Ķ����������
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
	for (auto i : Coin)	//��ÿһ��Ӳ�Ҷ�����л���
	{
		i->draw();
	}
}
