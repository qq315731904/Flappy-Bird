#include "SandDobstacle.h"
#include "Control.h"
extern Control* now;
void SandDobstacle::add(int i)
{
	obstacle.push_back(new Obstacle(i));
}
void SandDobstacle::drawLine()
{
	for (int j = 0; j < obstacle.size(); j++)	//���Ƴ��߿�Ķ����������
	{
		obstacle[j]->draw();	//�Զ�����л���
		if (obstacle[j]->x < -50)
		{
			if (!obstacle[j]->is_close)
			{
				now->Score++;
			}
			delete obstacle[j];
			obstacle.pop_front();
			j--;
		}
	}
}

