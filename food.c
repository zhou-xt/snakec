#include "food.h"

void initFood()
{
	int flag = 0; //判断位置合法的标志，0代表没有重复
	while (1)
	{
		//墙宽是 0 ~ 59 ，随机出 1~ 58
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
