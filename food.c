#include "food.h"

void initFood()
{
	int flag = 0; //�ж�λ�úϷ��ı�־��0����û���ظ�
	while (1)
	{
		//ǽ���� 0 ~ 59 ������� 1~ 58
		food.X = rand() % (WIDTH - 2) + 1;
		food.Y = rand() % (HEIGHT - 2) + 1;

		for (int i = 0; i < snake.size; i++)
		{
			if (snake.body[i].X == food.X && snake.body[i].Y == food.Y)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			break;
		}
	}
}
