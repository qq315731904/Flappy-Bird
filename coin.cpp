#include "Control.h"
#include"coin.h"
#include <cstdio>
extern Control* now;

void coin::draw()
{
	if (!is_close)	//判断当前对象是否已经被触碰，若未触碰则将该硬币显示出来若已触碰则不显示
	{
		char* t = new char[500];
		sprintf(t, "./Pic/medals_%d.png", this->shape);

		now->putImage(t, x, y, 50, 50);
		delete[] t;
	}
	if ((x>50 &&x<200)&&((now->Bird_y <= y+60 )&& now->Bird_y >= y)&&(!is_close))	//判断小鸟是否触碰到硬币，若触碰则执行
	{
		now->is_HitC = true;
		now->playSound("./Music/coin.wav");	//吃到硬币音效
		is_close = true;
		/*不同硬币种类对应不同分值*/
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