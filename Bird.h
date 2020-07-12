#pragma once
class Bird {
private:
	int x = 100, y = 430;	//设置小鸟初始位置
	int Psize = 100;	//设置小鸟大小
	int cnt = 5;	//控制图片变化速度
public:
	void draw();	//进行动画绘制
};