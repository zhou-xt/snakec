#pragma once
#include<stdio.h>
#include "wall.h"

//�ߵ�ÿ����εĽṹ��
struct BODY
{
	int X;
	int Y;
};

//�߽ṹ��
struct SNAKE
{
	struct BODY body[(WIDTH - 2) * (HEIGHT - 2)]; //�������ʾ����������
	int size; //�ߵĳ���
}snake;

//��ʼ����
void initSnake();

int offset_X; //���ƶ�����xƫ����
int offset_Y; //���ƶ�����yƫ����

int tile_x; //��βx����
int tile_y; //��βy����

int isRool; //ͷβѭ��
