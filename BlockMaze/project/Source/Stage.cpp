#include "Stage.h"

//const:�����������Ȃ��萔
//���ڐ����������Ɛl�i�ے肳���
//�����ł͂Ȃ������ŏ���
const int WIDTH = 12;
const int HIGHT = 8;
const int CHIP_SIZE = 40;

int map[HIGHT][WIDTH] = 
{
	{2,1,1,1,1,1,1,1,1,1,1,2},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,1,1,1,1,1,0,1},
	{1,0,1,0,0,0,0,0,0,1,0,1},
	{1,0,1,0,0,0,0,0,0,1,0,1},
	{1,0,1,1,1,1,1,1,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{2,1,1,1,1,1,1,1,1,1,1,2},
};


Stage::Stage()
{
	hImage = LoadGraph("data/image/parts.png");
}

Stage::~Stage()
{
	
}

void Stage::Draw()
{
	//x,y,�؂蔲��,�؂蔲��,40,40
	for (int j = 0; j < HIGHT; j++)//�c�uj�v
	{
		int y = j * 40 + 100;
		for (int i = 0; i < WIDTH; i++)//���ui�v
		{
			int x = i * 40 + 100;
			if (map[j][i] == 1)//�����K
			{
				DrawRectGraph(x, y, CHIP_SIZE*0, CHIP_SIZE*1, 40, 40, hImage, TRUE);
			}
			else if (map[j][i] == 2)//�R�C��
			{
			DrawRectGraph(x, y, CHIP_SIZE*3, CHIP_SIZE*0, 40, 40, hImage, TRUE);
			}
		}
	}

	
}