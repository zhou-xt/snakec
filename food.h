#pragma once
#include<stdio.h>
#include "wall.h"
#include "snake.h"

//食物结构体
struct FOOD
{
	int X;
	int Y;
}food;

//设置食物
void initFood();
