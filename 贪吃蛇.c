#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "snake.h"
#include "food.h"

int score = 0;//统计分数
int sleepTime = 300; //移动速度

void gotoxy(int x, int y)
{
	if (x == 0 && y == 0) //如果吃掉食物，蛇尾的 0,0不要改为空格
	{
		return;
	}

	COORD coord;
	coord.X = x;
	coord.Y = y;
	//设置控制台光标位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


//更新画面
void update()
{
	//设置蛇颜色为11
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	for (int i = 0; i < snake.size; i++)
	{
		gotoxy(snake.body[i].X, snake.body[i].Y);

		if (i == 0)
		{
			printf("@");
		}
		else
		{
			printf("#");
		}
	}

	//设置食物颜色为11
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	//设置食物
	gotoxy(food.X, food.Y);
	printf("X");

	//更新蛇尾
	gotoxy(tile_x, tile_y);
	printf(" ");

	//如果头尾循环，再次显示一次头
	if (isRool)
	{
		//设置蛇颜色为11
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		gotoxy(snake.body[0].X, snake.body[0].Y);
		putchar('@');
	}

	//统计分数
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);//设置分数颜色为9
	gotoxy(0, HEIGHT);
	printf("分数:%d\n", score);
}

void gameOver(int mode) //死亡情况  1为撞自身，2为撞墙
{
	//撞自身后，再次显示蛇头
	if (mode == 1)
	{
		//设置蛇颜色为11
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		gotoxy(snake.body[0].X, snake.body[0].Y);
		putchar('@');
	}

	//设置结束提示颜色为15
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(0, HEIGHT + 1);

	printf("Game Over\n");
	system("pause");
	exit(1);
}


int main()
{
	//去掉控制台光标
	CONSOLE_CURSOR_INFO  cci;
	cci.bVisible = FALSE;
	cci.dwSize = sizeof(cci);
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

	//设置墙颜色为12
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

	//初始化墙
	initWall();

	//初始化蛇
	initSnake();

	//初始化食物
	initFood();

	char key = 'd'; //默认移动方向向右
	char preKey = 'd'; //上一次的方向

	//让蛇移动起来
	while (snake.body[0].X >= 1 && snake.body[0].X <= WIDTH - 2
		&& snake.body[0].Y >= 1 && snake.body[0].Y <= HEIGHT - 2)
	{
		if (_kbhit()) //如果没有键盘输入则返回0
		{
			key = _getch();
		}

		//屏蔽180°转弯
		if (key == 'd' && preKey == 'a' || key == 'a' && preKey == 'd' ||
			key == 'w' && preKey == 's' || key == 's' && preKey == 'w')
		{
			key = preKey;
		}
		else
		{
			preKey = key;
		}

		switch (key)
		{
		case 'a':
			offset_X = -1;
			offset_Y = 0;
			break;
		case 'd':
			offset_X = 1;
			offset_Y = 0;
			break;
		case 's':
			offset_X = 0;
			offset_Y = 1;
			break;
		case 'w':
			offset_X = 0;
			offset_Y = -1;
			break;
		}

		//蛇和身体碰撞
		for (int i = 1; i < snake.size; i++)
		{
			if (snake.body[0].X == snake.body[i].X
				&& snake.body[0].Y == snake.body[i].Y)
			{
				gameOver(1);
			}
		}

		//蛇吃到食物  后面的移动蛇身代码已经添加了一个节点
		if (snake.body[0].X == food.X && snake.body[0].Y == food.Y)
		{
			snake.size++;
			score += 100;//吃到食物加分
			sleepTime -= 10;//吃到食物则提高难度
			initFood();
		}

		for (int i = snake.size - 1; i > 0; i--)
		{
			//用上一节身体给当前身体坐标赋值
			snake.body[i].X = snake.body[i - 1].X;
			snake.body[i].Y = snake.body[i - 1].Y;
		}

		snake.body[0].X += offset_X;
		snake.body[0].Y += offset_Y;

		//记录蛇尾坐标
		tile_x = snake.body[snake.size - 1].X;
		tile_y = snake.body[snake.size - 1].Y;

		update(); //更新显示

		Sleep(sleepTime);
	}

	//头尾循环
	if (snake.body[0].X == tile_x && snake.body[0].Y == tile_y)
	{
		isRool = 1;
	}
	else
	{
		isRool = 0;
	}

	//更新画面
	update();

	//蛇撞墙结束游戏
	gameOver(2);

	return 0;
}