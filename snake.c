#include "snake.h"

//��ʼ����
void initSnake()
{
	//����������
	snake.size = 3;

	//��ͷ
	snake.body[0].X = WIDTH / 2;
	snake.body[0].Y = HEIGHT / 2;

	snake.body[1].X = WIDTH / 2 - 1;
	snake.body[1].Y = HEIGHT / 2;

	snake.body[2].X = WIDTH / 2 - 2;
	snake.body[2].Y = HEIGHT / 2;
}
