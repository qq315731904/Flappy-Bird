#include "Obstacle.h"
#include "Control.h"
#include <cstdio>
extern Control* now;
void Obstacle::draw()
{
	char* t = new char[500];
	char* t1 = new char[500];
	/*六种不同障碍类型*/
	switch (this->shape)
	{
	case 0:
		sprintf(t, "./Pic/pipe_down.png");
		now->putImage(t, x, -280, 50, 320);
		sprintf(t1, "./Pic/pipe_up.png");
		now->putImage(t1, x, 500, 50, 500);
		if (x < 20 && now->is_HitO)	//判断是否碰撞，且小鸟是否已经离开碰撞范围，若未离开则处于无敌状态
		{
			now->is_HitO = false;	//若是则将now->is_HitO置为false方便下一个障碍对象进行判断
		}
		if ((x>50 && x < 200) && (now->Bird_y<20 || now->Bird_y > 440) && (!is_close) && (!now->is_HitO))	//判断是否在触碰范围且未被锁住且未处于无敌状态
		{
			is_close = true;
			now->is_HitO = true;
			now->Hp--;
			now->playSound("./Music/sublives.wav");
		}
		break;
		/*之后的判断与第一个相似*/
	case 1:
		sprintf(t, "./Pic/pipe_down.png");
		now->putImage(t, x, -240, 50, 320);
		sprintf(t1, "./Pic/pipe_up.png");
		now->putImage(t1, x, 280, 50, 500);
		if (x < 20 && now->is_HitO)
		{
			now->is_HitO = false;
		}
		if ((x > 50 && x < 200) && (now->Bird_y<50 || now->Bird_y > 220) && (!is_close) && (!now->is_HitO))
		{
			is_close = true;
			now->is_HitO = true;
			now->Hp--;
			now->playSound("./Music/sublives.wav");
		}
		break;
	case 2:
		sprintf(t, "./Pic/pipe_down.png");
		now->putImage(t, x, -240, 50, 360);
		sprintf(t1, "./Pic/pipe_up.png");
		now->putImage(t1, x, 320, 50, 400);
		if (x < 20 && now->is_HitO)
		{
			now->is_HitO = false;
		}
		if ((x > 50 && x < 200) && (now->Bird_y<90 || now->Bird_y > 260) && (!is_close) && (!now->is_HitO))
		{
			is_close = true;
			now->is_HitO = true;
			now->Hp--;
			now->playSound("./Music/sublives.wav");
		}
		break;
	case 3:
		sprintf(t, "./Pic/pipe_down.png");
		now->putImage(t, x, -20, 50, 180);
		sprintf(t1, "./Pic/pipe_up.png");
		now->putImage(t1, x, 360, 50, 360);
		if (x < 20 && now->is_HitO)
		{
			now->is_HitO = false;
		}
		if ((x > 50 && x < 200) && (now->Bird_y<130 || now->Bird_y > 300) && (!is_close) && (!now->is_HitO))
		{
			is_close = true;
			now->is_HitO = true;
			now->Hp--;
			now->playSound("./Music/sublives.wav");
		}
		break;
	case 4:
		sprintf(t, "./Pic/pipe_down.png");
		now->putImage(t, x, -20, 50, 220);
		sprintf(t1, "./Pic/pipe_up.png");
		now->putImage(t1, x, 420, 50, 420);
		if (x < 20 && now->is_HitO)
		{
			now->is_HitO = false;
		}
		if ((x > 50 && x < 200) && (now->Bird_y<170 || now->Bird_y > 360) && (!is_close) && (!now->is_HitO))
		{
			is_close = true;
			now->is_HitO = true;
			now->Hp--;
			now->playSound("./Music/sublives.wav");
		}
		break;
	case 5:
		sprintf(t, "./Pic/pipe_down.png");
		now->putImage(t, x, -20, 50, 260);
		sprintf(t1, "./Pic/pipe_up.png");
		now->putImage(t1, x, 440, 50, 460);
		if (x < 20 && now->is_HitO)
		{
			now->is_HitO = false;
		}
		if ((x > 50 && x < 200) && (now->Bird_y<210 || now->Bird_y > 380) && (!is_close) && (!now->is_HitO))
		{
			is_close = true;
			now->is_HitO = true;
			now->Hp--;
			now->playSound("./Music/sublives.wav");
		}
		break;
	case 6:
		sprintf(t, "./Pic/pipe_down.png");
		now->putImage(t, x, -20, 50, 300);
		sprintf(t1, "./Pic/pipe_up.png");
		now->putImage(t1, x, 480, 50, 480);
		if (x < 20 && now->is_HitO)
		{
			now->is_HitO = false;
		}
		if ((x > 50 && x < 200 )&& (now->Bird_y<250 || now->Bird_y > 420) && (!is_close)&&(!now->is_HitO))
		{
			is_close = true;
			now->is_HitO = true;
			now->Hp--;
			now->playSound("./Music/sublives.wav");
		}
		break;
	}
	delete[] t;
	delete[] t1;
	x -= now->Obstacle_dx;
}
Obstacle::Obstacle(int shape)
{
	this->shape = shape;
}
