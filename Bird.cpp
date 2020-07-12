#include "Bird.h"
#include "Control.h"
static int state = 0;
extern Control* now;	//控制类对象贯穿整个程序
void Bird::draw()
{
	/*判断鼠标是否按下，若按下则小鸟向上飞且开启煽动音效*/
	if (now->is_Mouse)
	{
		if (now->is_HitO)	//判断是否碰撞，若碰撞则进入无敌帧时间即小鸟开始闪烁
		{
			now->IF = 4;	//IF是无敌帧的缩写Invincible frame
		}
		else
		{
			now->IF = 3;	//若IF变回3则恢复正常状态
		}
		char* s = new char[500];
		sprintf(s, "./Pic/bird0_%d.png", state / cnt);	//cnt初始值为5，state初始值为0，state/cnt表示程序每执行5次更新一次图片
		y = y - now->Bird_dy1;	//小鸟y坐标减少即向上运动
		now->Bird_y = y;	//控制类对象now及时获得小鸟当前y坐标（x坐标固定）
		now->putImage(s, x, y, Psize, Psize);
		state++;	//进行程序执行次数计数
		if (state >= cnt * now->IF)state = 0;	//若state>=15则将state置0，即刚好显示完三张图片，小鸟的飞行动作由三张图片变换形成
		delete[] s;
	}
	/*若鼠标为按下则小鸟自动向下运动y++*/
	else
	{
		/*同上*/
		if (now->is_HitO)
		{
			now->IF = 4;
		}
		else
		{
			now->IF = 3;
		}
		char* s = new char[500];
		sprintf(s, "./Pic/bird0_%d.png", state / cnt);
		y += now->Bird_dy;
		now->Bird_y = y;
		now->putImage(s, x, y, Psize, Psize);
		state++;
		if (state == cnt * now->IF)state = 0;
		delete[] s;
	}
}
