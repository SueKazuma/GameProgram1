#include "Stage.h"
#include "Player.h"

//const:書き換えられない定数
//直接数字を書くと人格否定される
//数字ではなく文字で書く
const int WIDTH = 12;
const int HIGHT = 8;
const int CHIP_SIZE = 40;

int map[HIGHT][WIDTH] = 
{
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,1,1,1,1,1,0,1},
	{1,0,1,0,0,0,0,0,0,1,0,1},
	{1,0,1,0,0,0,0,0,0,1,0,1},
	{1,0,1,1,1,1,2,1,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,9,1},
};


Stage::Stage()
{
	hImage = LoadGraph("data/image/parts.png");

	//9を探して、Playerを置く
	for (int j = 0; j < HIGHT; j++) 
	{
		for (int i = 0; i < WIDTH; i++)
		{
			if (map[j][i] == 9)
			{
				Player* p = Instantiate<Player>();
				p->position.x = CHIP_SIZE *j;
				p->position.y = CHIP_SIZE *i;
			}
		}
	}
}

Stage::~Stage()
{
	
}

void Stage::Draw()
{
	//x,y,切り抜き,切り抜き,40,40
	for (int j = 0; j < HIGHT; j++)//縦「j」
	{
		int y = j * 40 + 100;
		for (int i = 0; i < WIDTH; i++)//幅「i」
		{
			int x = i * 40 + 100;
			if (map[j][i] == 1)//レンガ
			{
				DrawRectGraph(x, y, CHIP_SIZE*0, CHIP_SIZE*1, 40, 40, hImage, TRUE);
			}
			else if (map[j][i] == 2)//コイン
			{
			DrawRectGraph(x, y, CHIP_SIZE*3, CHIP_SIZE*0, 40, 40, hImage, TRUE);
			}
		}
	}

	
}
