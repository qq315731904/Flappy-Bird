#pragma once
#include <random>
class coin
{
private:
	int shape = 0;
public:
	int x = 1160,y = rand() % 640;	//Ӳ��λ���������Ӳ�ҵ�������
	bool is_close = false;	//����ǰӲ�Ҷ����ѱ�С�������򽫸ö�����Ĵ����жϹرձ����δ���
	void draw();/*����Ӳ��*/
	coin(const int shape);//��һ��������ѡ��Ӳ������
};