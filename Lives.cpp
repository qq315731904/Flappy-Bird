#include "Lives.h"
#include "Control.h"
#include <cstdio>
extern Control* now;
void Lives::draw()
{
	if (!is_close)
	{
		now->putImage("./Pic/Lives.png", x, y, 50, 50);
	}
	x -= now->Lives_dx;
	if ((x > 50 && x < 200) && (now->Bird_y <= y + 60 && now->Bird_y >= y) && (!is_close))
	{
		if (now->Hp < 3)
		{
			now->Hp++;
			now->playSound("./Music/addlives.wav");	//³Ôµ½°®ÐÄÒôÐ§
		}
		is_close = true;
	}
}
Lives::Lives(int y)
{
	this->y = y;
}