#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "snake.h"
#include "food.h"

int score = 0;//ͳ�Ʒ���
int sleepTime = 300; //�ƶ��ٶ�

void gotoxy(int x, int y)
{
	if (x == 0 && y == 0) //����Ե�ʳ���β�� 0,0��Ҫ��Ϊ�ո�
	{
		return;
	}

	COORD coord;
	coord.X = x;
	coord.Y = y;
	//���ÿ���̨���λ��
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


//���»���
void update()
{
	//��������ɫΪ11
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

	//����ʳ����ɫΪ11
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	//����ʳ��
	gotoxy(food.X, food.Y);
	printf("X");

	//������β
	gotoxy(tile_x, tile_y);
	printf(" ");

	//���ͷβѭ�����ٴ���ʾһ��ͷ
	if (isRool)
	{
		//��������ɫΪ11
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		gotoxy(snake.body[0].X, snake.body[0].Y);
		putchar('@');
	}

	//ͳ�Ʒ���
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);//���÷�����ɫΪ9
	gotoxy(0, HEIGHT);
	printf("����:%d\n", score);
}

void gameOver(int mode) //�������  1Ϊײ����2Ϊײǽ
{
	//ײ������ٴ���ʾ��ͷ
	if (mode == 1)
	{
		//��������ɫΪ11
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		gotoxy(snake.body[0].X, snake.body[0].Y);
		putchar('@');
	}

	//���ý�����ʾ��ɫΪ15
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(0, HEIGHT + 1);

	printf("Game Over\n");
	system("pause");
	exit(1);
}


int main()
{
	//ȥ������̨���
	CONSOLE_CURSOR_INFO  cci;
	cci.bVisible = FALSE;
	cci.dwSize = sizeof(cci);
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

	//����ǽ��ɫΪ12
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

	//��ʼ��ǽ
	initWall();

	//��ʼ����
	initSnake();

	//��ʼ��ʳ��
	initFood();

	char key = 'd'; //Ĭ���ƶ���������
	char preKey = 'd'; //��һ�εķ���

	//�����ƶ�����
	while (snake.body[0].X >= 1 && snake.body[0].X <= WIDTH - 2
		&& snake.body[0].Y >= 1 && snake.body[0].Y <= HEIGHT - 2)
	{
		if (_kbhit()) //���û�м��������򷵻�0
		{
			key = _getch();
		}

		//����180��ת��
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

		//�ߺ�������ײ
		for (int i = 1; i < snake.size; i++)
		{
			if (snake.body[0].X == snake.body[i].X
				&& snake.body[0].Y == snake.body[i].Y)
			{
				gameOver(1);
			}
		}

		//�߳Ե�ʳ��  ������ƶ���������Ѿ������һ���ڵ�
		if (snake.body[0].X == food.X && snake.body[0].Y == food.Y)
		{
			snake.size++;
			score += 100;//�Ե�ʳ��ӷ�
			sleepTime -= 10;//�Ե�ʳ��������Ѷ�
			initFood();
		}

		for (int i = snake.size - 1; i > 0; i--)
		{
			//����һ���������ǰ�������긳ֵ
			snake.body[i].X = snake.body[i - 1].X;
			snake.body[i].Y = snake.body[i - 1].Y;
		}

		snake.body[0].X += offset_X;
		snake.body[0].Y += offset_Y;

		//��¼��β����
		tile_x = snake.body[snake.size - 1].X;
		tile_y = snake.body[snake.size - 1].Y;

		update(); //������ʾ

		Sleep(sleepTime);
	}

	//ͷβѭ��
	if (snake.body[0].X == tile_x && snake.body[0].Y == tile_y)
	{
		isRool = 1;
	}
	else
	{
		isRool = 0;
	}

	//���»���
	update();

	//��ײǽ������Ϸ
	gameOver(2);

	return 0;
}