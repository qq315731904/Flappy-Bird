#include "SandDobstacle.h"
#include "Control.h"
extern Control* now;
void SandDobstacle::add(int i)
{
	obstacle.push_back(new Obstacle(i));
}
void SandDobstacle::drawLine()
{
	for (int j = 0; j < obstacle.size(); j++)	//对移出边框的对象进行销毁
	{
		obstacle[j]->draw();	//对对象进行绘制
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

