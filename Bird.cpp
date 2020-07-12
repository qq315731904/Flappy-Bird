#include "Bird.h"
#include "Control.h"
static int state = 0;
extern Control* now;	//���������ᴩ��������
void Bird::draw()
{
	/*�ж�����Ƿ��£���������С�����Ϸ��ҿ���ɿ����Ч*/
	if (now->is_Mouse)
	{
		if (now->is_HitO)	//�ж��Ƿ���ײ������ײ������޵�֡ʱ�伴С��ʼ��˸
		{
			now->IF = 4;	//IF���޵�֡����дInvincible frame
		}
		else
		{
			now->IF = 3;	//��IF���3��ָ�����״̬
		}
		char* s = new char[500];
		sprintf(s, "./Pic/bird0_%d.png", state / cnt);	//cnt��ʼֵΪ5��state��ʼֵΪ0��state/cnt��ʾ����ÿִ��5�θ���һ��ͼƬ
		y = y - now->Bird_dy1;	//С��y������ټ������˶�
		now->Bird_y = y;	//���������now��ʱ���С��ǰy���꣨x����̶���
		now->putImage(s, x, y, Psize, Psize);
		state++;	//���г���ִ�д�������
		if (state >= cnt * now->IF)state = 0;	//��state>=15��state��0�����պ���ʾ������ͼƬ��С��ķ��ж���������ͼƬ�任�γ�
		delete[] s;
	}
	/*�����Ϊ������С���Զ������˶�y++*/
	else
	{
		/*ͬ��*/
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
