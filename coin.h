#pragma once
#include <random>
class coin
{
private:
	int shape = 0;
public:
	int x = 1160,y = rand() % 640;	//硬币位置随机生成硬币的有坐标
	bool is_close = false;	//若当前硬币对象已被小鸟触碰到则将该对象里的触碰判断关闭避免多次触碰
	void draw();/*绘制硬币*/
	coin(const int shape);//传一个整数，选择硬币种类
};