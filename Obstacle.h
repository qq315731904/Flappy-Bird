#pragma once
class Obstacle
{
public:
	int shape = 0;
	int x = 960;
	bool is_close = false;
	void draw();/*���²������ϰ�*/
	Obstacle(const int shape);//��һ��������ѡ���ϰ�������
};