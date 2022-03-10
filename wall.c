#include "wall.h"

//墙及显示信息制作
void initWall()
{

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (i == 0 || j == 0 || i == HEIGHT - 1 || j == WIDTH - 1)
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}
		if (i == 5)
		{
			printf("\t贪食蛇");
		}
		if (i == 6)
		{
			printf("\t上 : w");
		}
		if (i == 7)
		{
			printf("\t下 : s");
		}
		if (i == 8)
		{
			printf("\t左 : a");
		}
		if (i == 9)
		{
			printf("\t右 : d");
		}
		printf("\n");
	}
}
