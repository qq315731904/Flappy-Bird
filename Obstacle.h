#pragma once
class Obstacle
{
public:
	int shape = 0;
	int x = 960;
	bool is_close = false;
	void draw();/*更新并绘制障碍*/
	Obstacle(const int shape);//传一个整数，选择障碍物类型
};