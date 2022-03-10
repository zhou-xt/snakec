#pragma once
#include<stdio.h>
#include "wall.h"

//蛇的每个身段的结构体
struct BODY
{
	int X;
	int Y;
};

//蛇结构体
struct SNAKE
{
	struct BODY body[(WIDTH - 2) * (HEIGHT - 2)]; //蛇最大显示的身体数量
	int size; //蛇的长度
}snake;

//初始化蛇
void initSnake();

int offset_X; //蛇移动方向x偏移量
int offset_Y; //蛇移动方向y偏移量

int tile_x; //蛇尾x坐标
int tile_y; //蛇尾y坐标

int isRool; //头尾循环
