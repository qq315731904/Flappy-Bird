#include "Control.h"
#include"coin.h"
#include <cstdio>
extern Control* now;

void coin::draw()
{
	if (!is_close)	//�жϵ�ǰ�����Ƿ��Ѿ�����������δ�����򽫸�Ӳ����ʾ�������Ѵ�������ʾ
	{
		char* t = new char[500];
		sprintf(t, "./Pic/medals_%d.png", this->shape);

		now->putImage(t, x, y, 50, 50);
		delete[] t;
	}
	if ((x>50 &&x<200)&&((now->Bird_y <= y+60 )&& now->Bird_y >= y)&&(!is_close))	//�ж�С���Ƿ�����Ӳ�ң���������ִ��
	{
		now->is_HitC = true;
		now->playSound("./Music/coin.wav");	//�Ե�Ӳ����Ч
		is_close = true;
		/*��ͬӲ�������Ӧ��ͬ��ֵ*/
		switch (this->shape)
		{
		case 3:
			now->Score += 1;
			break;
		case 2:
			now->Score += 3;
			break;
		case 1:
			now->Score += 5;
			break;
		case 0:
			now->Score += 10;
			break;

		}
	}
	x -= now->coin_dx;

}
coin::coin(int shape)
{
	this->shape=shape;
};